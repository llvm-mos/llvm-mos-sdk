// clang-format off
// text2data.cpp : nesdoug bug fix fork
// changes marked with **
// originally by Shiru

//#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>


#define OUT_NESASM  0
#define OUT_CA65    1
#define OUT_ASM6    2
#define OUT_LLVM    3

char DB[8];
char DW[8];
char LL[8];
char LOW[8];

#define MIN_PATTERN_LEN		6
#define MAX_REPEAT_CNT		60

#define MAX_SUB_SONGS		((256-5)/14)
#define MAX_ROWS			256
#define MAX_PATTERNS		(128*MAX_SUB_SONGS)
#define MAX_ORDER			(128*MAX_SUB_SONGS)
#define MAX_INSTRUMENTS		64
#define MAX_ENVELOPES		128
#define MAX_ENVELOPE_LEN	256

unsigned int keep_instruments = 0; // ** if != 0, don't remove any instruments
unsigned int no_warnings = 0; // ** if != 0, silence warning about unsupported effects
unsigned char song_name[MAX_SUB_SONGS][256] = { 0 }; // **

typedef struct {
	unsigned char note;		//0 empty position, 1 rest note, 2 and above note starting from C-0
	char instrument;		//0 no change, 1 and above instrument number
	char effect;
	unsigned char parameter;
} channelStruct;

typedef struct {
	channelStruct channel[5];
	unsigned char speed;
} rowStruct;

typedef struct {
	rowStruct row[MAX_ROWS];
	unsigned char length;
} patternStruct;

typedef struct {
	int speed;
	int tempo;
	int pattern_length;
	int order_length;
	int order_loop;

	patternStruct pattern[MAX_PATTERNS];
} songStruct;

typedef struct {
	short int volume;
	short int pitch;
	short int arpeggio;
	short int duty;
	short int id;

	bool in_use;
} instrumentStruct;

typedef struct {
	short int value[MAX_ENVELOPE_LEN];
	short int length;
	short int loop;
	short int out_id;

	bool in_use;
} envelopeStruct;

typedef struct {
	int off;
	int size;
} dpcmEntryStruct;

typedef struct {
	int off;
	int size;
	int pitch;
	int loop;
	int id;
} sampleStruct;

envelopeStruct envelopeVolume[MAX_ENVELOPES];
envelopeStruct envelopeArpeggio[MAX_ENVELOPES];
envelopeStruct envelopePitch[MAX_ENVELOPES];
envelopeStruct envelopeDuty[MAX_ENVELOPES];

songStruct song_original;
songStruct song_split;

instrumentStruct instruments[MAX_INSTRUMENTS];
sampleStruct sample_list[MAX_INSTRUMENTS];

unsigned char dpcm[16384];
int dpcm_size;

char* text_src = NULL;
int text_size;

FILE* outfile = NULL;

typedef struct {
	unsigned char data[MAX_ENVELOPE_LEN + 2];
	int size;
} outputEnvelopeStruct;

outputEnvelopeStruct outputEnvelopes[MAX_ENVELOPES * 4 + 1];

int outputEnvelopeCount;

int subSongsCount;

#define MAX_PACKED_ROWS		256
#define MAX_PACKED_PATTERNS	(5*MAX_ORDER*MAX_SUB_SONGS)
#define MAX_PACKED_SIZE		MAX_PACKED_ROWS*4

typedef struct {
	unsigned char data[MAX_PACKED_SIZE];
	short int length;
	short int ref_id;
	short int ref_length;
} packedPatternStruct;

packedPatternStruct packedPatterns[MAX_PACKED_PATTERNS];

int packedCount;
int referenceId;

int outtype;

int channels;

char songName[1024];
char songName1[1024];



bool text_open(char* filename)
{
	FILE* file;
	int ps, pd, size;
	char* text;
	char c;

	file = fopen(filename, "rb");

	if (!file) return false;

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	text = (char*)malloc(size);

	fread(text, size, 1, file);
	fclose(file);

	if (text_src)
	{
		free(text_src);
		text_src = NULL;
	}

	text_src = (char*)malloc(size + 1);	//extra byte in case no 0x0d to remove in the source text somehow

	ps = 0;
	pd = 0;

	while (ps < size)
	{
		c = text[ps++];

		if (c == '\t') c = ' ';

		if (c != 0x0d) text_src[pd++] = c;
	}

	text_src[pd++] = 0x0a;

	text_size = pd;

	if (text)
	{
		free(text);
		text = NULL;
	}

	return true;
}


void text_close(void)
{
	if (text_src)
	{
		free(text_src);
		text_src = NULL;
		text_size = 0;
	}
}


int text_skip_line(int off)
{
	while (off < text_size)
	{
		if (text_src[off++] == 0x0a) break;
	}

	return off;
}


int text_skip_spaces(int off)
{
	while (off < text_size) if (text_src[off] == ' ') ++off; else break;

	return off;
}


int text_skip_dec_and_spaces(int off)
{
	char n;

	off = text_skip_spaces(off);

	while (off < text_size)
	{
		n = text_src[off];

		if (!((n >= '0' && n <= '9') || n == '-')) break;

		++off;
	}

	return text_skip_spaces(off);
}


int text_skip_hex_and_spaces(int off)
{
	char n;

	off = text_skip_spaces(off);

	while (off < text_size)
	{
		n = text_src[off];

		if (!((n >= '0' && n <= '9') || (n >= 'a' && n <= 'f') || (n >= 'A' && n <= 'F'))) break;

		++off;
	}

	return text_skip_spaces(off);
}


int text_find_tag(const char* tag, int off)
{
	int i;

	for (i = off; i < text_size - (int)strlen(tag); ++i)
	{
		if (!memcmp(&text_src[i], tag, strlen(tag))) return text_skip_spaces(i + strlen(tag));
	}

	return -1;
}


int text_find_tag_start_sub_song(const char* tag, int off)
{
	int i;

	for (i = off; i < text_size - (int)strlen(tag); ++i)
	{
		if (!memcmp(&text_src[i], "TRACK", 5)) return -1;

		if (!memcmp(&text_src[i], tag, strlen(tag))) return text_skip_spaces(i + strlen(tag));
	}

	return -1;
}


int text_skip_tag(int off)
{
	while (off < text_size)
	{
		if (text_src[off] <= ' ') break;

		++off;
	}

	return text_skip_spaces(off);
}


int text_find_tag_section(const char* tag, int off)
{
	while (off < text_size - (int)strlen(tag))
	{
		if (text_src[off] == '[') break;

		if (!memcmp(&text_src[off], tag, strlen(tag))) return text_skip_spaces(off + strlen(tag));

		++off;
	}

	return -1;
}


int text_find_tag_start(const char* tag, int off)
{
	int i;

	for (i = off; i < text_size - (int)strlen(tag); ++i)
	{
		if (!memcmp(&text_src[i], tag, strlen(tag))) return i;
	}

	return -1;
}


int text_read_dec(int off)
{
	int n, num, sign;

	num = 0;

	if (text_src[off] == '-')
	{
		++off;
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	while (off < text_size)
	{
		n = text_src[off++];

		if (n < '0' || n>'9') break;

		num = num * 10 + n - '0';
	}

	return num * sign;
}


int hex(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;

	return -1;
}


int text_read_hex(int off)
{
	int n, num;

	num = 0;

	while (off < text_size)
	{
		n = hex(text_src[off++]);

		if (n < 0) break;

		num = num * 16 + n;
	}

	return num;
}



void clear_packed_patterns(void)
{
	memset(packedPatterns, 0, sizeof(packedPatterns));

	packedCount = 0;	//clear packed patterns list, it is common for all sub songs
	referenceId = 0;	//global reference id
}



void clear_song(void)
{
	memset(&song_original, 0, sizeof(song_original));
}



void clear_instruments(void)
{
	memset(&instruments, 0, sizeof(instruments));
	memset(&envelopeVolume, 0, sizeof(envelopeVolume));
	memset(&envelopeArpeggio, 0, sizeof(envelopeArpeggio));
	memset(&envelopePitch, 0, sizeof(envelopePitch));
	memset(&envelopeDuty, 0, sizeof(envelopeDuty));

	memset(dpcm, 0, sizeof(dpcm));

	dpcm_size = 0;

	memset(sample_list, 0, sizeof(sample_list));

	subSongsCount = 0;
}


void parse_error(int off, const char* str)
{
	int ptr, row, col;

	if (off < 0)
	{
		printf("Parsing error: %s\n", str);
	}
	else
	{
		row = 1;
		col = 1;
		ptr = 0;

		while (ptr < off)
		{
			if (text_src[ptr++] == '\n')
			{
				++row;
				col = 0;
			}

			++col;
		}

		printf("Parsing error (row %i,col %i): %s\n", row, col, str);
	}

	exit(1);
}


void parse_error_ptn(int song, int pos, int row, int chn, const char* str)
{
	printf("Parsing error (song:%2.2i pos:%2.2x row:%2.2x chn %i): %s\n", song + 1, pos, row, chn, str);

	exit(1);
}


void parse_instruments_old(void)
{
	const char* seqTypeCount[4] = { "SequencesVolumeCount=","SequencesArpeggioCount=","SequencesPitchCount=","SequencesDutyCount=" };
	const char* seqTypeSection[4] = { "[SequencesVolume]","[SequencesArpeggio]","[SequencesPitch]","[SequencesDuty]" };
	const char* seqTypeName[4] = { "SequenceVolume","SequenceArpeggio","SequencePitch","SequenceDuty" };
	char str[128];
	int i, j, n, id, off, ptr, cnt, pos, type, ins, soff, doff, dsize, val, size, ins_id;
	envelopeStruct* env;
	dpcmEntryStruct dpcm_list[64];

	subSongsCount = 1;//old text format does not support multisong

					  //parse instruments

	off = 0;
	ins_id = 0;

	for (i = 0; i < MAX_INSTRUMENTS; ++i)
	{
		off = text_find_tag("[Instrument", off);

		if (off < 0) break;

		ins = text_read_dec(off);

		if (ins > 63) parse_error(off, "Only 64 instruments (0..63) are supported");

		off = text_skip_line(off);

		n = text_find_tag_section("SequenceVolume=", off);

		instruments[ins].volume = n < 0 ? -1 : text_read_dec(n);

		n = text_find_tag_section("SequenceArpeggio=", off);

		instruments[ins].arpeggio = n < 0 ? -1 : text_read_dec(n);

		n = text_find_tag_section("SequencePitch=", off);

		instruments[ins].pitch = n < 0 ? -1 : text_read_dec(n);

		n = text_find_tag_section("SequenceDuty=", off);

		instruments[ins].duty = n < 0 ? -1 : text_read_dec(n);

		instruments[ins].id = ins_id;

		if (keep_instruments)
		{
			instruments[ins].in_use = true; // **
		}

		++ins_id;
	}

	//parse envelopes

	for (type = 0; type < 4; ++type)
	{
		off = text_find_tag(seqTypeCount[type], 0);

		if (off < 0) parse_error(off, "SequenceTypeCount not found");

		cnt = text_read_dec(off);
		id = 0;

		off = text_find_tag(seqTypeSection[type], off);

		while (cnt)
		{
			sprintf(str, "%s%i=", seqTypeName[type], id);

			ptr = text_find_tag_section(str, off);

			if (ptr >= 0)
			{
				pos = 0;

				switch (type)
				{
				default: // ** fix build error, overly cautious compiler
				case 0: env = &envelopeVolume[id]; break;
				case 1: env = &envelopeArpeggio[id]; break;
				case 2: env = &envelopePitch[id]; break;
				case 3: env = &envelopeDuty[id]; break;
				}

				env->loop = -1;

				while (ptr < text_size)
				{
					if (text_src[ptr] < 32) break;

					if (text_src[ptr] == '|')
					{
						env->loop = pos;
						++ptr;
					}

					n = text_read_dec(ptr);

					if (n < -64 || n>63) parse_error(off, "Envelope value is out of range (-64..63)\n");

					env->value[pos++] = n;

					while (ptr < text_size)
					{
						if (text_src[ptr] < 32) break;
						if (text_src[ptr++] == ',') break;
					}
				}

				env->length = pos;

				--cnt;
			}

			++id;
		}
	}

	//parse samples

	doff = 0;
	dsize = 0;

	soff = text_find_tag_start("[DMC", 0);

	if (soff < 0) return;//no sample section found

	memset(dpcm_list, 0, sizeof(dpcm_list));

	for (i = 0; i < 64; i++) dpcm_list[i].off = -1;

	for (i = 0; i < 64; i++)
	{
		sprintf(str, "[Sample%i]", i + 1);

		off = text_find_tag(str, soff);

		if (off >= 0)
		{
			off = text_find_tag("SampleSize=", off);

			if (off < 0) parse_error(off, "No SampleSize found");

			size = text_read_dec(off);

			off = text_find_tag("SampleData=$", off);

			if (off < 0) parse_error(off, "No SampleData found");

			dpcm_list[i].off = doff >> 6;
			size = 0;
			j = 0;

			while (off < text_size)
			{
				if (text_src[off] == '\n') break;

				if (!j)
				{
					val = hex(text_src[off]) << 4;
					j = 1;
				}
				else
				{
					val |= hex(text_src[off]);
					dpcm[doff++] = val;
					++dsize;
					++size;
					j = 0;
				}

				++off;
			}

			dpcm_list[i].size = size >> 4;
			doff = ((doff >> 6) + 1) << 6;
		}
	}

	off = text_find_tag("[DMC0]", soff);

	if (off >= 0)
	{
		off = text_find_tag("SamplesAssigned=", off);

		if (off < 0) parse_error(off, "No SamplesAssigned found");

		for (i = 0; i < 96; i++)
		{
			val = text_read_dec(off);
			off = text_skip_dec_and_spaces(off);

			if (i >= 1 * 12 && i < 6 * 12 + 3 && val)
			{
				sample_list[i - 1 * 12].off = dpcm_list[val - 1].off;
				sample_list[i - 1 * 12].size = dpcm_list[val - 1].size;
			}

			++off;
		}

		off = text_find_tag("SamplesPitch=", off);

		if (off < 0) parse_error(off, "No SamplesPitch found");

		for (i = 0; i < 96; i++)
		{
			val = text_read_dec(off);
			off = text_skip_dec_and_spaces(off);

			if (i >= 1 * 12 && i < 6 * 12 + 3)
			{
				sample_list[i - 1 * 12].pitch = val;
			}

			++off;
		}

		off = text_find_tag("SamplesLoop=", off);

		if (off < 0) parse_error(off, "No SamplesLoop found");

		for (i = 0; i < 96; i++)
		{
			val = text_read_dec(off);
			off = text_skip_dec_and_spaces(off);

			if (i >= 1 * 12 && i < 6 * 12 + 3)
			{
				sample_list[i - 1 * 12].loop = val;
			}

			++off;
		}
	}

	dpcm_size = doff;
}


void parse_song_old(void)
{
	char str[128];
	int n, pos, row, chn, note, ins, off;
	bool song_break, pattern_break;

	off = 0;

	if ((off = text_find_tag("Speed=", off)) < 0) parse_error(off, "Speed not found");

	song_original.speed = text_read_dec(off);
	song_original.tempo = 150;

	if ((off = text_find_tag("FramesCount=", off)) < 0) parse_error(off, "Frames count not found");

	song_original.order_length = text_read_dec(off);

	if ((off = text_find_tag("PatternLength=", off)) < 0) parse_error(off, "Pattern length not found");

	song_original.pattern_length = text_read_dec(off);

	song_break = false;

	for (pos = 0; pos < song_original.order_length; ++pos)
	{
		song_original.pattern[pos].length = song_original.pattern_length;

		sprintf(str, "[Frame%i]", pos);

		off = text_find_tag(str, off);

		if (off < 0) parse_error(off, "Frame not found");

		off = text_skip_line(off);

		pattern_break = false;

		for (row = 0; row < song_original.pattern_length; ++row)
		{
			n = text_read_hex(off);

			if (n != row) parse_error(off, "Unexpected row number");

			off += 3;

			for (chn = 0; chn < channels; ++chn)
			{
				switch (text_src[off])
				{
				case '.': note = 0; break;
				case '-': note = 1; break;
				case 'C': note = 2; break;
				case 'D': note = 4; break;
				case 'E': note = 6; break;
				case 'F': note = 7; break;
				case 'G': note = 9; break;
				case 'A': note = 11; break;
				case 'B': note = 13; break;
				default: parse_error(off, "Unexpected character in the note field");
				}

				if (text_src[off + 1] == '#') ++note;

				if (note > 1)
				{
					note += 12 * text_read_dec(off + 2);//add octave

					if (note < 12 + 2 || note >= 12 * 6 + 2 + 3) parse_error_ptn(0, pos, row, chn, "Note is out of supported range (C-1..D-6)");

					note -= 12;//correct range
				}

				if (chn == 3 && note > 1) note = ((note - 2 + 11) & 15) + 2;//uniform notes in the noise channel

				if (chn == 4 && note > 1)//check note range in the DPCM channel
				{
					if (note < 2 * 12 + 2 || note>3 * 12 - 1 + 2) parse_error_ptn(0, pos, row, chn, "DPCM note is out of supported range (C-3..B-3)");

					note = note - 2 * 12;
				}

				if (text_src[off + 4] == '.') ins = -1; else ins = text_read_hex(off + 4);

				if (ins > 63) parse_error_ptn(0, pos, row, chn, "Instrument number is out of range (0..63)");

				song_original.pattern[pos].row[row].channel[chn].note = note;
				song_original.pattern[pos].row[row].channel[chn].instrument = ins;

				if (ins >= 0) instruments[ins].in_use = true;

				switch (text_src[off + 9])//supported effects
				{
				case 0: case '.': break;//no effect

				case 'B'://end song and loop to a provided order list position
					song_original.order_length = pos + 1;
					song_original.order_loop = text_read_hex(off + 10);
					song_original.pattern[pos].length = row + 1;
					song_break = true;

					if (song_original.order_loop > pos) parse_error_ptn(0, pos, row, chn, "Bxx loop position can't be a forward reference");

					break;

				case 'D'://end pattern early
					song_original.pattern[pos].length = row + 1;
					pattern_break = true;
					break;

				case 'F'://change speed
					song_original.pattern[pos].row[row].speed = text_read_hex(off + 10);
					break;

				default:
					parse_error_ptn(0, pos, row, chn, "Unsupported effect");
				}

				off += 13;
			}

			if (song_break || pattern_break) break;
		}

		if (song_break) break;
	}
}


void parse_instruments(void)
{
	int i, n, off, ptr, id, type, loop, ins, octave, note, pitch, size, ins_id;
	envelopeStruct* env;
	static char str[1024];

	//check how many sub songs are there

	off = 0;
	subSongsCount = 0;

	while (1)
	{
		off = text_find_tag("TRACK", off);

		if (off < 0) break;

		++subSongsCount;
	}

	if (subSongsCount > MAX_SUB_SONGS) parse_error(0, "Too many sub songs");

	//parse envelopes

	off = text_find_tag("# Macros", 0);

	if (off < 0) parse_error(off, "Macros section not found");

	while (off < text_size)
	{
		off = text_find_tag("MACRO", off);

		if (off < 0) break;

		type = text_read_dec(off);//macro group number

		off = text_skip_dec_and_spaces(off);

		id = text_read_dec(off);//macro id in a group

		if (id > MAX_ENVELOPES) parse_error(off, "Macro number is too large");

		off = text_skip_dec_and_spaces(off);

		loop = text_read_dec(off);//envelope loop

		off = text_skip_dec_and_spaces(off);

		n = text_read_dec(off);//unknown parameter

		off = text_skip_dec_and_spaces(off);

		n = text_read_dec(off);//unknown parameter

		off = text_skip_dec_and_spaces(off);

		if (text_src[off] != ':') parse_error(off, "Unexpected macro format");

		switch (type)
		{
		case 0: env = &envelopeVolume[id]; break;//volume
		case 1: env = &envelopeArpeggio[id]; break;//arpeggio
		case 2: env = &envelopePitch[id]; break;//pitch
		case 4: env = &envelopeDuty[id]; break;//duty
		default: env = NULL;
		}

		if (env)
		{
			off += 2;
			ptr = 0;

			while (off < text_size)
			{
				if (text_src[off] == '\n') break;

				if (ptr >= MAX_ENVELOPE_LEN) parse_error(off, "Macro is too long");

				env->value[ptr++] = text_read_dec(off);

				off = text_skip_dec_and_spaces(off);
			}

			env->length = ptr;
			env->loop = loop;
		}
	}

	//parse instruments

	for (i = 0; i < MAX_INSTRUMENTS; ++i) sample_list[i].id = -1;

	off = text_find_tag("# Instruments", off);

	if (off < 0) parse_error(off, "Instruments section not found");

	ins_id = 0;

	while (off < text_size)
	{
		off = text_skip_line(off);

		if (!memcmp(&text_src[off], "INST2A03", 8))
		{
			off = text_skip_tag(off);

			ins = text_read_dec(off);//instrument number

			if (ins < 0 || ins >= MAX_INSTRUMENTS) parse_error(off, "Wrong instrument number");

			if (ins > 63) parse_error(off, "Only 64 instruments (0..63) supported");

			off = text_skip_dec_and_spaces(off);

			instruments[ins].volume = text_read_dec(off);//volume envelope id

			if (instruments[ins].volume < 0)
			{
				sprintf(str, "Instrument %i does not have volume envelope", ins);
				parse_error(off, str);
			}

			off = text_skip_dec_and_spaces(off);

			instruments[ins].arpeggio = text_read_dec(off);//arpeggio envelope id

			off = text_skip_dec_and_spaces(off);

			instruments[ins].pitch = text_read_dec(off);//pitch envelope id

			off = text_skip_dec_and_spaces(off);

			n = text_read_dec(off);//unused hi-pitch envelope id

			off = text_skip_dec_and_spaces(off);

			instruments[ins].duty = text_read_dec(off);//duty cycle envelope id

			instruments[ins].id = ins_id;

			if (keep_instruments) {
				instruments[ins].in_use = true; // **
			}

			++ins_id;

			continue;
		}

		if (!memcmp(&text_src[off], "KEYDPCM", 7))
		{
			off = text_skip_tag(off);

			ins = text_read_dec(off);//instrument number

			if (ins != 0) continue;

			off = text_skip_dec_and_spaces(off);

			octave = text_read_dec(off);//octave

			off = text_skip_dec_and_spaces(off);

			note = text_read_dec(off);//note

			if ((octave * 12 + note) < 1 * 12 || (octave * 12 + note) >= 6 * 12 + 3) parse_error(off, "DPCM samples could only be assigned to notes C-1..D-6");

			ins = (octave - 1) * 12 + note;

			off = text_skip_dec_and_spaces(off);

			id = text_read_dec(off);//sample number

			off = text_skip_dec_and_spaces(off);

			pitch = text_read_dec(off);//pitch

			off = text_skip_dec_and_spaces(off);

			loop = text_read_dec(off);//loop

			off = text_skip_dec_and_spaces(off);

			n = text_read_dec(off);//unknown

			off = text_skip_dec_and_spaces(off);

			n = text_read_dec(off);//unknown

			sample_list[ins].id = id;
			sample_list[ins].loop = loop;
			sample_list[ins].pitch = pitch;
			sample_list[ins].size = 0;

			continue;
		}

		break;
	}

	//parse sample data

	ptr = 0;

	off = text_find_tag("# DPCM samples", off);

	while (off < text_size)
	{
		off = text_find_tag("DPCMDEF", off);

		if (off < 0) break;

		id = text_read_dec(off);
		note = -1;

		for (i = 0; i < MAX_INSTRUMENTS; ++i)
		{
			if (sample_list[i].id == id)
			{
				note = i;
				break;
			}
		}

		if (note < 0) continue;

		off = text_skip_dec_and_spaces(off);

		size = text_read_dec(off);

		for (i = 0; i < MAX_INSTRUMENTS; ++i)
		{
			if (sample_list[i].id == id)
			{
				sample_list[i].off = ptr >> 6;
				sample_list[i].size = size >> 4;
			}
		}

		while (off < text_size)
		{
			off = text_skip_line(off);

			if (memcmp(&text_src[off], "DPCM :", 6)) break;

			off += 7;

			while (off < text_size)
			{
				if (text_src[off] == '\n') break;

				n = text_read_hex(off);
				off = text_skip_hex_and_spaces(off);

				dpcm[ptr++] = n;
				--size;
			}
		}

		if (size != 0) parse_error(off, "Actual DPCM sample size does not match its definition");

		ptr = ((ptr >> 6) + 1) << 6;
	}

	for (i = 0; i < MAX_INSTRUMENTS; ++i) if (sample_list[i].off < 0) sample_list[i].off = 0;

	dpcm_size = ptr;
}


void parse_song(int subsong, bool header_only)
{
	static patternStruct pattern[MAX_PATTERNS];
	static int order[MAX_ORDER][5];

	char str[128];
	int i, n, row, pos, off, ptn, chn, note, ins, maxptn, off_prev;
	int shortest; // **
	channelStruct* nsrc, * ndst;

	if (subsong >= subSongsCount) parse_error(0, "No sub song found");

	off = text_find_tag("# Tracks", 0);

	for (i = 0; i <= subsong; ++i) off = text_find_tag("TRACK", off);

	if (off < 0) parse_error(off, "Can't find track section");

	off = text_skip_spaces(off);

	song_original.pattern_length = text_read_dec(off);

	off = text_skip_dec_and_spaces(off);

	song_original.speed = text_read_dec(off);

	off = text_skip_dec_and_spaces(off);

	song_original.tempo = text_read_dec(off);

	for (int a = 0; a < 6; a++) { //** begin changes
		if (text_src[off] == '\"') break;
		off++;
	}
	off++;

	for (int a = 0; a < 256; a++) {

		if (text_src[off] == '\"') {
			song_name[subsong][a] = 0;
			break;
		}
		song_name[subsong][a] = text_src[off];
		off++;
	} //** end

	if (header_only) return;

	//parse order list

	pos = 0;
	maxptn = 0;

	off = text_find_tag_start("ORDER", off);

	while (off < text_size)
	{
		if (text_src[off] != 'O') break;

		order[pos][0] = text_read_hex(off + 11);
		order[pos][1] = text_read_hex(off + 14);
		order[pos][2] = text_read_hex(off + 17);
		order[pos][3] = text_read_hex(off + 20);
		order[pos][4] = text_read_hex(off + 23);

		for (chn = 0; chn < channels; ++chn) if (order[pos][chn] > maxptn) maxptn = order[pos][chn];

		off = text_skip_line(off);

		++pos;
	}

	song_original.order_length = pos;

	//parse patterns

	ptn = 0;

	for (i = 0; i <= maxptn; ++i)
	{
		pattern[ptn].length = song_original.pattern_length;

		sprintf(str, "PATTERN %2.2X", i);

		off_prev = off;

		off = text_find_tag_start_sub_song(str, off);

		if (off < 0)//pattern not found, could be caused by the Famitracker cleanup, just skip it
		{
			off = off_prev;

			for (row = 0; row < song_original.pattern_length; ++row)
			{
				for (chn = 0; chn < channels; ++chn)
				{
					pattern[ptn].row[row].channel[chn].note = 0;
					pattern[ptn].row[row].channel[chn].instrument = 0;
					pattern[ptn].row[row].channel[chn].effect = 0;
					pattern[ptn].row[row].channel[chn].parameter = 0;
				}
			}

			++ptn;

			continue;
		}

		off = text_skip_line(off);

		for (row = 0; row < song_original.pattern_length; ++row)
		{
			if (memcmp(&text_src[off], "ROW", 3))
			{
				printf("%i\n", row);
				parse_error(off, "No row definition found ");
			}

			if (text_read_hex(off + 4) != row) parse_error(off, "Unexpected row number");

			for (chn = 0; chn < channels; ++chn)
			{
				while (text_src[off++] != ':');//skip to a channel position, regardless of number of effect columns

				++off;

				n = text_src[off];

				if (chn != 3)//normal channels
				{
					switch (n)
					{
					case '.': note = 0; break;
					case '-': note = 1; break;
					case 'C': note = 2; break;
					case 'D': note = 4; break;
					case 'E': note = 6; break;
					case 'F': note = 7; break;
					case 'G': note = 9; break;
					case 'A': note = 11; break;
					case 'B': note = 13; break;
					default: parse_error(off, "Unexpected character in the note field");
					}

					if (text_src[off + 1] == '#') ++note;

					if (note > 1)
					{
						note += 12 * text_read_dec(off + 2);//add octave

						if (note < 2 + 12 || note >= 2 + 12 + 63) parse_error(off, "Note is out of supported range (C-1..D-6)");

						note -= 12;//correct range
					}
				}
				else//noise channel has different note format
				{
					switch (n)
					{
					case '.': note = 0; break;
					case '-': note = 1; break;
					default:
						n = hex(n);

						if (n >= 0) note = ((n + 15) & 15) + 2; else parse_error(off, "Unexpected character in the note field");
					}
				}

				if (text_src[off + 4] == '.') ins = -1; else ins = text_read_hex(off + 4);

				if (ins > 63) parse_error(off, "Instrument number is out of range (0..63)");

				pattern[ptn].row[row].channel[chn].note = note;
				pattern[ptn].row[row].channel[chn].instrument = ins;
				pattern[ptn].row[row].channel[chn].effect = text_src[off + 9];
				pattern[ptn].row[row].channel[chn].parameter = text_read_hex(off + 10);

				if (ins >= 0) instruments[ins].in_use = true;
			}

			off = text_skip_line(off);
		}

		++ptn;
	}

	//convert order list and patterns into song, reordering patterns into linear order

	for (pos = 0; pos < song_original.order_length; ++pos)
	{
		song_original.pattern[pos].length = song_original.pattern_length;

		shortest = song_original.pattern_length; // ** set full size, then shrink if D00/Bxx

		for (chn = 0; chn < channels; ++chn)
		{
			for (row = 0; row < song_original.pattern_length; ++row)
			{
				nsrc = &pattern[order[pos][chn]].row[row].channel[chn];
				ndst = &song_original.pattern[pos].row[row].channel[chn];

				ndst->note = nsrc->note;
				ndst->instrument = nsrc->instrument;

				switch (nsrc->effect)//supported effects
				{
				case 0: case '.': break;//no effect

				case 'B'://end song and loop to a provided order list position
				{
					if (row > shortest) break; // **
					shortest = row + 1;

					song_original.order_length = pos + 1;
					song_original.order_loop = nsrc->parameter;

					song_original.pattern[pos].length = row + 1;

					row = MAX_ROWS;//stop parsing current pattern

					if (song_original.order_loop > pos) parse_error_ptn(subsong, pos, row, chn, "Bxx loop position can't be a forward reference");
				}
				break;

				case 'D'://end pattern early
				{
					song_original.pattern[pos].length = row + 1;

					row = MAX_ROWS;//stop parsing current pattern

					if (nsrc->parameter) parse_error_ptn(subsong, pos, row, chn, "Dxx value can only be zero");

					if (song_original.pattern[pos].length < shortest)
					{
						shortest = song_original.pattern[pos].length; // **
					}
				}
				break;

				case 'F'://change speed
				{
					song_original.pattern[pos].row[row].speed = nsrc->parameter;
				}
				break;

				default:
				{
					if (!no_warnings)
					{
						printf("%c", nsrc->effect);
						parse_error_ptn(subsong, pos, row, chn, "Unsupported effect");
					}
				}
				}
			}
		}

		song_original.pattern[pos].length = shortest; // **
	}
}



//remove repeating instrument numbers and repeating speed values

void song_cleanup_instrument_numbers(void)
{
	int chn, pos, row, ins, speed;
	channelStruct* ch;
	int insloop[5];
	bool stop;

	for (chn = 0; chn < channels; ++chn) insloop[chn] = -1;

	for (chn = 0; chn < channels; ++chn)
	{
		ins = -1;
		speed = 0;

		for (pos = 0; pos < song_original.order_length; ++pos)
		{
			for (row = 0; row < song_original.pattern[pos].length; ++row)
			{
				ch = &song_original.pattern[pos].row[row].channel[chn];

				if (chn < 4)//pulse, triangle, and noise channels
				{
					if (ch->note < 2 && ch->instrument >= 0) ch->instrument = -1;//ignore instrument numbers at empty rows and rest notes

					if (ch->instrument >= 0)
					{
						if ((pos == song_original.order_loop) && (insloop[chn] < 0)) // **
						{
							insloop[chn] = ins; // **
						}
						if (ins != ch->instrument)
						{
							ins = ch->instrument;
						}
						else
						{
							ch->instrument = -1;
						}
					}
				}
				else//dpcm channel
				{
					ch->instrument = -1;
				}

				if (!chn)
				{
					if (song_original.pattern[pos].row[row].speed)
					{
						if (speed == song_original.pattern[pos].row[row].speed)
						{
							song_original.pattern[pos].row[row].speed = 0;
						}
						else
						{
							speed = song_original.pattern[pos].row[row].speed;
						}
					}
				}
			}
		}

		if (ins < 0) ins = 0;

		//if (chn<4) insloop[chn] = ins; // **
	}

	//set current instrument number for first actual note after the loop point

	for (chn = 0; chn < 4; ++chn)
	{
		if (insloop[chn] < 0) continue;

		stop = false;

		for (pos = song_original.order_loop; pos < song_original.order_length; ++pos)
		{
			for (row = 0; row < song_original.pattern[pos].length; ++row)
			{
				ch = &song_original.pattern[pos].row[row].channel[chn];

				if (ch->note > 1)
				{
					if (ch->instrument < 0) ch->instrument = insloop[chn];

					stop = true;
					break;
				}
			}

			if (stop) break;
		}
	}

	if (!song_original.pattern[song_original.order_loop].row[0].speed) song_original.pattern[song_original.order_loop].row[0].speed = speed;
}



//remove extra trailing zeroes in volume envelopes, cut duty cycle envelopes length

void envelopes_cleanup(void)
{
	int i, j;

	for (i = 0; i < MAX_ENVELOPES; ++i)
	{
		if (envelopeVolume[i].loop < 0)
		{
			for (j = envelopeVolume[i].length - 1; j > 0; --j) if (!envelopeVolume[i].value[j] && !envelopeVolume[i].value[j - 1]) --envelopeVolume[i].length; else break;
		}

		if (envelopeDuty[i].length > 1) envelopeDuty[i].length = 1;
	}
}



//change pitch envelopes from absolute to accumulated value

void envelope_pitch_convert(void)
{
	int i, j, val;

	for (i = 0; i < MAX_ENVELOPES; ++i)
	{
		val = 0;

		for (j = 0; j < envelopePitch[i].length; ++j)
		{
			val += envelopePitch[i].value[j];

			if (val < -64) val = -64;
			if (val > 63) val = 63;

			envelopePitch[i].value[j] = val;
		}
	}
}

/*
void song_text_dump(songStruct* s)
{
	const char* noteNames[12] = { "C-","C#","D-","D#","E-","F-","F#","G-","G#","A-","A#","B-" };
	const char* typeNames[4] = { "volume","arpeggio","pitch","duty" };
	int i, j, k, type, note, instrument;
	envelopeStruct* env;
	rowStruct* row;

	//general settings

	printf("speed %i\n", s->speed);
	printf("tempo %i\n", s->tempo);
	printf("order length %i\n", s->order_length);
	printf("order loop %i\n", s->order_loop);
	printf("\n");

	//instrument settings

	for (i = 0; i < MAX_INSTRUMENTS; ++i)
	{
		if (instruments[i].in_use)
		{
			printf("instrument %i\n", i);
			printf(" volume   %i\n", instruments[i].volume);
			printf(" arpeggio %i\n", instruments[i].arpeggio);
			printf(" pitch    %i\n", instruments[i].pitch);
			printf(" duty     %i\n", instruments[i].duty);
			printf("\n");
		}
	}

	//envelope sequences

	for (type = 0; type < 4; ++type)
	{
		for (i = 0; i < MAX_ENVELOPES; ++i)
		{
			switch (type)
			{
			default: // ** fix build error, overly cautious compiler
			case 0: env = &envelopeVolume[i]; break;
			case 1: env = &envelopeArpeggio[i]; break;
			case 2: env = &envelopePitch[i]; break;
			case 3: env = &envelopeDuty[i]; break;
			}

			if (env->length)
			{
				printf("env.%s %i=", typeNames[type], i);

				for (j = 0; j < env->length; ++j)
				{
					if (env->loop == j) printf(">");

					printf("%i ", env->value[j]);
				}

				printf("\n");
			}
		}
	}

	printf("\n");

	//patterns

	for (i = 0; i < s->order_length; ++i)
	{
		printf("order position %i ", i);

		if (i == s->order_loop) printf("(loop point)");

		printf("\n\n");

		for (j = 0; j < s->pattern[i].length; ++j)
		{
			row = &s->pattern[i].row[j];

			printf("%2.2X: ", j);

			for (k = 0; k < channels; ++k)
			{
				note = row->channel[k].note;
				instrument = row->channel[k].instrument;

				switch (note)
				{
				case 0: printf("..."); break;
				case 1: printf("---"); break;
				default:
					printf("%s%i", noteNames[(note - 2) % 12], (note - 2) / 12 + 1);
				}

				if (instrument >= 0) printf(" %2.2X ", instrument); else printf(" .. ");
			}

			if (row->speed) printf(" %2.2X", row->speed);

			printf("\n");
		}

		printf("\n");
	}
}
*/


void output_open(const char* filename)
{
	outfile = fopen(filename, "wt");
}



int output_dump_byte_array(unsigned char* data, int length, bool test)
{
	int col, ptr;

	if (test) return length;

	ptr = 0;
	col = 0;

	while (ptr < length)
	{
		if (!col) fprintf(outfile, "\t%s ", DB);

		fprintf(outfile, "$%2.2x", data[ptr++]);

		++col;

		if (col >= 16 || ptr == length)
		{
			fprintf(outfile, "\n");
			col = 0;
		}
		else
		{
			fprintf(outfile, ",");
		}
	}

	return length;
}



int output_process_envelope(short int* value, int length, int loop)
{
	static unsigned char data[MAX_ENVELOPE_LEN];
	int i, j, val, prev_val, rle_cnt, ptr, ptr_loop, size;

	if (length <= 0) return 0;//default envelope

	ptr = 0;
	ptr_loop = -1;

	prev_val = value[0] + 1;//prevent rle match
	rle_cnt = 0;

	for (j = 0; j < length; ++j)
	{
		if (j == loop) ptr_loop = ptr;

		val = value[j];

		if (val < -64) val = -64;
		if (val > 63) val = 63;

		val += 192;

		if (prev_val != val || j == length - 1)
		{
			if (rle_cnt)
			{
				if (rle_cnt == 1)
				{
					data[ptr++] = prev_val;
				}
				else
				{
					while (rle_cnt > 126)
					{
						data[ptr++] = 126;
						rle_cnt -= 126;
					}

					data[ptr++] = rle_cnt;
				}

				rle_cnt = 0;
			}

			data[ptr++] = val;

			prev_val = val;
		}
		else
		{
			++rle_cnt;
		}
	}

	if (ptr_loop < 0) ptr_loop = ptr - 1; else if (data[ptr_loop] < 128) ++ptr_loop;//ptr_loop increased if it points at RLEd repeats of a previous value

	data[ptr++] = 0;
	data[ptr++] = ptr_loop;

	size = ptr;

	for (i = 0; i < outputEnvelopeCount; ++i)
	{
		if (!memcmp(outputEnvelopes[i].data, data, size)) return i;
	}

	memcpy(outputEnvelopes[outputEnvelopeCount].data, data, size);

	outputEnvelopes[outputEnvelopeCount].size = size;

	++outputEnvelopeCount;

	return outputEnvelopeCount - 1;
}



int output_header(char* songname, int song)
{
	int sub, chn, tempo_pal, tempo_ntsc, size, from, to;

	fprintf(outfile, ";this file for FamiTone2 library generated by text2data tool\n\n");

	fprintf(outfile, "%s_music_data:\n", songname);
	fprintf(outfile, "\t%s %i\n", DB, subSongsCount);
	fprintf(outfile, "\t%s %sinstruments\n", DW, LL);
	fprintf(outfile, "\t%s %ssamples-3\n", DW, LL);

	size = 5;

	if (song < 0)
	{
		from = 0;
		to = subSongsCount;
	}
	else
	{
		from = song;
		to = from + 1;

	}
	for (sub = from; sub < to; ++sub)
	{
		parse_song(sub, true);

		fprintf(outfile, "\t%s ", DW);

		for (chn = 0; chn < 5; ++chn)
		{
			if (chn < channels) fprintf(outfile, "%ssong%ich%i,", LL, sub, chn); else fprintf(outfile, "0,");
		}

		tempo_pal = 256 * song_original.tempo / (50 * 60 / 24);
		tempo_ntsc = 256 * song_original.tempo / (60 * 60 / 24);

		fprintf(outfile, "%i,%i ; ", tempo_pal, tempo_ntsc);

		for (int a = 0; a < 256; a++) { // **
			if (song_name[sub][a] == 0) break;
			fprintf(outfile, "%c", song_name[sub][a]);
		}
		fprintf(outfile, "\n");

		size += 14;
	}

	fprintf(outfile, "\n");

	return size;
}



int output_instruments(void)
{
	int i, size, duty;

	size = 0;

	//add default envelope, used for any undefined envelopes, it simply keeps 0

	outputEnvelopeCount = 0;

	outputEnvelopes[outputEnvelopeCount].data[0] = 0xc0;
	outputEnvelopes[outputEnvelopeCount].data[1] = 0x00;
	outputEnvelopes[outputEnvelopeCount].data[2] = 0x00;
	outputEnvelopes[outputEnvelopeCount].size = 3;

	++outputEnvelopeCount;

	//mark all used envelopes

	for (i = 0; i < MAX_ENVELOPES; ++i)
	{
		envelopeVolume[i].in_use = false;
		envelopeArpeggio[i].in_use = false;
		envelopePitch[i].in_use = false;
	}

	for (i = 0; i < MAX_INSTRUMENTS; ++i)
	{
		if (!instruments[i].in_use) continue;

		//envelopeVolume[instruments[i].volume].in_use = true;
		//envelopeArpeggio[instruments[i].arpeggio].in_use = true;
		//envelopePitch[instruments[i].pitch].in_use = true;
		
		if (instruments[i].volume >= 0)
		{
			envelopeVolume[instruments[i].volume].in_use = true;
		}
		if (instruments[i].arpeggio >= 0)
		{
			envelopeArpeggio[instruments[i].arpeggio].in_use = true;
		}
		if (instruments[i].pitch >= 0)
		{
			envelopePitch[instruments[i].pitch].in_use = true;
		}
		// ** fixed a [-1] undefined behavior bug
	}

	//convert all envelopes into byte data, add into common list, remove duplicates

	for (i = 0; i < MAX_ENVELOPES; ++i) envelopeVolume[i].out_id = output_process_envelope(envelopeVolume[i].value, envelopeVolume[i].in_use ? envelopeVolume[i].length : 0, envelopeVolume[i].loop);
	for (i = 0; i < MAX_ENVELOPES; ++i) envelopeArpeggio[i].out_id = output_process_envelope(envelopeArpeggio[i].value, envelopeArpeggio[i].in_use ? envelopeArpeggio[i].length : 0, envelopeArpeggio[i].loop);
	for (i = 0; i < MAX_ENVELOPES; ++i) envelopePitch[i].out_id = output_process_envelope(envelopePitch[i].value, envelopePitch[i].in_use ? envelopePitch[i].length : 0, envelopePitch[i].loop);

	//output instrument list

	fprintf(outfile, "%sinstruments:\n", LL);

	for (i = 0; i < MAX_INSTRUMENTS; ++i)
	{
		if (!instruments[i].in_use) continue;

		if (envelopeDuty[instruments[i].duty].length > 0) duty = envelopeDuty[instruments[i].duty].value[0] & 3; else duty = 0;

		fprintf(outfile, "\t%s $%2.2x ;instrument $%2.2x\n", DB, (duty << 6) | 0x30, i);
		fprintf(outfile, "\t%s ", DW);
		if (instruments[i].volume < 0) // ** fixed a [-1] undefined behavior bug
		{
			fprintf(outfile, "%senv0,", LL);
		}
		else
		{
			fprintf(outfile, "%senv%i,", LL, envelopeVolume[instruments[i].volume].out_id);
		}
		if (instruments[i].arpeggio < 0)
		{
			fprintf(outfile, "%senv0,", LL);
		}
		else
		{
			fprintf(outfile, "%senv%i,", LL, envelopeArpeggio[instruments[i].arpeggio].out_id);
		}
		if (instruments[i].pitch < 0)
		{
			fprintf(outfile, "%senv0\n", LL);
		}
		else
		{
			fprintf(outfile, "%senv%i\n", LL, envelopePitch[instruments[i].pitch].out_id);
		}
		//fprintf(outfile, "%senv%i,", LL, envelopeVolume[instruments[i].volume].out_id);
		//fprintf(outfile, "%senv%i,", LL, envelopeArpeggio[instruments[i].arpeggio].out_id);
		//fprintf(outfile, "%senv%i\n", LL, envelopePitch[instruments[i].pitch].out_id);
		fprintf(outfile, "\t%s $00\n", DB);

		size += 2 * 3 + 2;
	}

	fprintf(outfile, "\n");

	//output samples list

	fprintf(outfile, "%ssamples:\n", LL);

	if (dpcm_size)
	{
		for (i = 0; i < 63; ++i)
		{
			fprintf(outfile, "\t%s $%2.2x+__dpcm_offset,$%2.2x,$%2.2x\t;%i\n", DB, sample_list[i].off, sample_list[i].size, sample_list[i].pitch | ((sample_list[i].loop & 1) << 6), i + 1);
			size += 3;
		}

		fprintf(outfile, "\n");
	}

	//output envelope data

	for (i = 0; i < outputEnvelopeCount; ++i)
	{
		fprintf(outfile, "%senv%i:\n", LL, i);

		size += output_dump_byte_array(outputEnvelopes[i].data, outputEnvelopes[i].size, false);
	}

	return size;
}



int output_song(int sub, int spdchn, bool test)
{
	static int ins_renumber[MAX_INSTRUMENTS];
	int i, ins, chn, srow, pos, ptr, note, size, ref, pcnt, pref, len, n1, n2, nrow, empty, ref_len;
	static packedPatternStruct tptn;
	rowStruct* row;
	patternStruct* ptn;

	//prepare instrument renumbering list

	ins = 0;

	for (i = 0; i < MAX_INSTRUMENTS; ++i)
	{
		if (instruments[i].in_use)
		{
			ins_renumber[i] = ins;
			++ins;
		}
		else
		{
			ins_renumber[i] = 0;
		}
	}

	//process song data

	pcnt = packedCount;
	pref = referenceId;

	size = 0;

	if (!test) fprintf(outfile, "\n");

	for (chn = 0; chn < channels; ++chn)
	{
		if (!test)
		{
			fprintf(outfile, "\n; ");

			for (int a = 0; a < 256; a++) {
				if (song_name[sub][a] == 0) break; // **
				fprintf(outfile, "%c", song_name[sub][a]);
			}
			fprintf(outfile, "\n");

			fprintf(outfile, "%ssong%ich%i:\n", LL, sub, chn);
		}

		if (chn == spdchn)//default speed
		{
			ptr = 0;

			tptn.data[ptr++] = 0xfb;
			tptn.data[ptr++] = song_split.speed;

			tptn.length = ptr;

			size += output_dump_byte_array(tptn.data, tptn.length, test);
		}

		for (pos = 0; pos < song_split.order_length; ++pos)
		{
			if (!test && pos == song_split.order_loop) fprintf(outfile, "%ssong%ich%iloop:\n", LL, sub, chn);

			ptr = 0;

			ptn = &song_split.pattern[pos];

			//convert a single pattern

			len = song_split.pattern[pos].length;
			srow = 0;
			ref_len = len;//pattern length without repeating empty rows

			while (srow < len)
			{
				if (ptr >= MAX_PACKED_SIZE) parse_error(0, "Not enough room in the tptn array");

				row = &ptn->row[srow++];

				note = row->channel[chn].note;

				if (chn == spdchn && row->speed)//speed change
				{
					tptn.data[ptr++] = 0xfb;
					tptn.data[ptr++] = row->speed;
				}

				if (note > 0)
				{
					//check if there is instrument change

					ins = row->channel[chn].instrument;

					if (ins >= 0) tptn.data[ptr++] = 0x80 | (ins_renumber[ins] << 1);

					//check if the note is followed by an empty row followed by a note

					n1 = 0;
					n2 = 0;

					if (srow + 0 < len)
					{
						n1 = ptn->row[srow + 0].channel[chn].note;

						if (chn == spdchn && ptn->row[srow + 0].speed) n1 = 1;
					}

					if (srow + 1 < len)
					{
						n2 = ptn->row[srow + 1].channel[chn].note;

						if (chn == spdchn && ptn->row[srow + 1].speed) n2 = 1;
					}

					nrow = (!n1 && n2) ? 0x01 : 0x00;//next empty row flag

					tptn.data[ptr++] = ((note - 1) << 1) | nrow;//0 rest note, 1..60 are octaves 1-5

					if (nrow)
					{
						++srow;
						--ref_len;
					}

					continue;
				}

				//count how many empty lines are there

				empty = 0;

				while (srow < len)
				{
					if (empty >= MAX_REPEAT_CNT) break;
					if (ptn->row[srow].channel[chn].note) break;
					if (chn == spdchn && ptn->row[srow].speed) break;

					++srow;
					++empty;
				}

				ref_len -= empty;

				tptn.data[ptr++] = 0x81 | (empty << 1);
			}

			tptn.length = ptr;
			tptn.ref_length = ref_len;

			//search for data match in the common data list

			ref = -1;

			if (tptn.length > 4)	//search data matches that is longer than the reference itself
			{
				for (i = 0; i < packedCount; ++i)
				{
					if (tptn.length <= packedPatterns[i].length)
					{
						if (!memcmp(tptn.data, packedPatterns[i].data, tptn.length))//match found
						{
							ref = i;
							break;
						}
					}
				}
			}

			if (ref < 0)//no match found, put data into output and the common data list
			{
				if (packedCount >= MAX_PACKED_PATTERNS) parse_error(0, "Not enough room in the common data list");

				memcpy(packedPatterns[packedCount].data, tptn.data, tptn.length);

				packedPatterns[packedCount].length = tptn.length;
				packedPatterns[packedCount].ref_length = tptn.ref_length;
				packedPatterns[packedCount].ref_id = referenceId;

				++packedCount;

				if (!test) fprintf(outfile, "%sref%i:\n", LL, referenceId);

				size += output_dump_byte_array(tptn.data, tptn.length, test);
			}
			else//match found, put reference into output
			{
				if (!test)
				{
					fprintf(outfile, "\t%s $ff,$%2.2x\n", DB, ref_len);
					fprintf(outfile, "\t%s %sref%i\n", DW, LL, packedPatterns[ref].ref_id);
				}

				size += 4;
			}

			++referenceId;
		}

		if (!test)
		{
			fprintf(outfile, "\t%s $fd\n", DB);//end of stream
			fprintf(outfile, "\t%s %ssong%ich%iloop\n", DW, LL, sub, chn);
		}

		size += 3;
	}

	if (test)//do not add packed patterns into the common list while in test mode
	{
		packedCount = pcnt;
		referenceId = pref;
	}

	return size;
}



void output_close(void)
{
	if (outfile)
	{
		fclose(outfile);
		outfile = NULL;
	}
}



//split songs into shorter patterns by dividing pattern lengths by the factor

void split_song(int factor)
{
	int spos, srow, dpos, drow, nlen, cnt;

	//check if all patterns are shorter than the minimal length after split

	cnt = 0;

	for (spos = 0; spos < song_original.order_length; ++spos) if (song_original.pattern[spos].length / factor < MIN_PATTERN_LEN) ++cnt;

	if (cnt == song_original.order_length) factor = 1;//don't do split in this case, to make optimal split search faster

													  //split patterns

	memset(&song_split, 0, sizeof(song_split));

	song_split.speed = song_original.speed;
	song_split.tempo = song_original.tempo;

	dpos = 0;

	for (spos = 0; spos < song_original.order_length; ++spos)
	{
		if (spos == song_original.order_loop) song_split.order_loop = dpos;

		nlen = song_original.pattern[spos].length / factor;

		if (nlen < MIN_PATTERN_LEN) nlen = MIN_PATTERN_LEN;

		drow = 0;

		for (srow = 0; srow < song_original.pattern[spos].length; ++srow)
		{
			memcpy(&song_split.pattern[dpos].row[drow], &song_original.pattern[spos].row[srow], sizeof(rowStruct));

			song_split.pattern[dpos].row[drow].speed = song_original.pattern[spos].row[srow].speed;

			++drow;

			if (drow >= nlen || srow == song_original.pattern[spos].length - 1)
			{
				song_split.pattern[dpos].length = drow;

				++dpos;

				if (dpos >= MAX_PATTERNS) parse_error(0, "Patterns array is not large enough");

				drow = 0;
			}
		}
	}

	song_split.order_length = dpos;
}



//find best conversion settings and proceed with output

int process_and_output_song(int sub)
{
	int size, spdchn, factor, size_min, best_channel, best_factor;

	size_min = 65536;
	best_channel = 0;
	best_factor = 1;

	for (spdchn = 0; spdchn < channels; ++spdchn)
	{
		for (factor = 1; factor <= song_original.pattern_length / MIN_PATTERN_LEN; ++factor)
		{
			split_song(factor);

			size = output_song(sub, spdchn, true);

			if (size < size_min)
			{
				size_min = size;
				best_channel = spdchn;
				best_factor = factor;
			}
		}
	}

	split_song(best_factor);

	//song_text_dump(&song_split);

	return output_song(sub, best_channel, false);
}



void exit_proc(void)
{
	text_close();
	output_close();
}



int main(int argc, char* argv[])
{
	FILE* file;
	char inname[1024], outname[1024], outname1[1024], dpcmname[1024];
	int i, size_header, size_instruments, size_song[MAX_SUB_SONGS], size_total, sub;
	char c;
	bool separate;

	printf("\n---famitone version 2d Mar 11 2022---\n\n");

	if (argc < 2)
	{
		printf("text2data for FamiTone2 NES audio library\n");
		printf("by Shiru (shiru@mail.ru), 04'17\n\n");
		printf("Usage: text2data.exe song.txt [-ca65,-asm6,-nesasm][-ch1..5][-s][-allin][-Wno]\n");

		return 0;
	}

	outtype = OUT_LLVM;
	strcpy(inname, "");
	channels = 5;//process all channels
	separate = false;//export all subsongs as one file

	for (i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-ca65")) outtype = OUT_CA65;
		if (!strcmp(argv[i], "-asm6")) outtype = OUT_ASM6;
		if (!strcmp(argv[i], "-nesasm")) outtype = OUT_NESASM;
		if (!strcmp(argv[i], "-ch5"))  channels = 5;
		if (!strcmp(argv[i], "-ch4"))  channels = 4;
		if (!strcmp(argv[i], "-ch3"))  channels = 3;
		if (!strcmp(argv[i], "-ch2"))  channels = 2;
		if (!strcmp(argv[i], "-ch1"))  channels = 1;
		if (!strcmp(argv[i], "-s"))    separate = true;
		if (!strcmp(argv[i], "-allin"))    keep_instruments = 1; // **
		if (!strcmp(argv[i], "-Wno"))    no_warnings = 1;

		if (argv[i][0] != '-') strcpy(inname, argv[i]);
	}

	atexit(exit_proc);

	if (!text_open(inname))
	{
		printf("Can't open file '%s'\n", inname);
		return 1;
	}

	//generate output filenames and song name

	strcpy(outname, inname);

	for (i = strlen(outname) - 1; i >= 0; --i)
	{
		if (outname[i] == '.')
		{
			outname[i] = 0;
			break;
		}
	}

	strcpy(songName, outname);
	strcpy(dpcmname, outname);
	strcat(dpcmname, ".dmc");

	for (i = strlen(songName) - 1; i >= 0; --i)
	{
		c = songName[i];

		if (c == '\\' || c == '/')
		{
			strcpy(songName, &songName[i + 1]);
			break;
		}

		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) songName[i] = '_';
	}

	//process data

	printf("Output format: ");

	switch (outtype)
	{
	case OUT_NESASM:
		printf("NESASM");
		strcpy(DB, ".db");
		strcpy(DW, ".dw");
		strcpy(LL, ".");
		strcpy(LOW, "LOW");
		break;

	case OUT_CA65:
		printf("CA65");
		strcpy(DB, ".byte");
		strcpy(DW, ".word");
		strcpy(LL, "@");
		strcpy(LOW, ".lobyte");
		break;

	case OUT_ASM6:
		printf("Asm6");
		strcpy(DB, "db");
		strcpy(DW, "dw");
		strcpy(LL, "@");
		strcpy(LOW, "<");
		break;

	case OUT_LLVM:
		printf("LLVM");
		strcpy(DB, ".byte");
		strcpy(DW, ".word");
		strcpy(LL, ".L");
		strcpy(LOW, "<");
		break;
	}

	printf(", ");

	if (!separate) printf("all songs in single file\n"); else printf("each song in a separate file\n");

	if (text_find_tag("FamiTracker text export", 0) >= 0) // ** removed #
	{
		printf("Input format: FamiTracker export\n");

		if (!separate)
		{
			clear_packed_patterns();
			clear_instruments();
			parse_instruments();

			for (sub = 0; sub < subSongsCount; ++sub)//mark all used instruments in all subsongs
			{
				clear_song();
				parse_song(sub, false);
				song_cleanup_instrument_numbers();
			}

			envelopes_cleanup();
			envelope_pitch_convert();

			if (outtype != OUT_CA65 && outtype != OUT_LLVM) strcat(outname, ".asm"); else strcat(outname, ".s");

			output_open(outname);

			size_header = output_header(songName, -1);
			size_instruments = output_instruments();

			clear_packed_patterns();

			for (sub = 0; sub < subSongsCount; ++sub)
			{
				clear_song();
				parse_song(sub, false);
				song_cleanup_instrument_numbers();

				size_song[sub] = process_and_output_song(sub);
			}

			output_close();

			size_total = size_header + size_instruments;

			printf("Header:     %i\n", size_header);
			printf("Instrument: %i\n", size_instruments);

			for (i = 0; i < subSongsCount; ++i)
			{
				printf("Sub song %i: %i\n", i, size_song[i]);
				size_total += size_song[i];
			}

			printf("\nTotal data size: %i bytes\n", size_total);
		}
		else
		{
			clear_packed_patterns();
			clear_instruments();
			parse_instruments();
			envelopes_cleanup();
			envelope_pitch_convert();

			for (sub = 0; sub < subSongsCount; ++sub)
			{
				for (i = 0; i < MAX_INSTRUMENTS; ++i) instruments[i].in_use = false;

				clear_song();
				parse_song(sub, false);
				song_cleanup_instrument_numbers();

				sprintf(outname1, "%s_%i", outname, sub);

				if (outtype != OUT_CA65 && outtype != OUT_LLVM) strcat(outname1, ".asm"); else strcat(outname1, ".s");

				output_open(outname1);

				sprintf(songName1, "%s_%i", songName, sub);

				size_header = output_header(songName1, sub);
				size_instruments = output_instruments();

				clear_packed_patterns();

				size_song[sub] = process_and_output_song(sub);

				output_close();

				printf("Sub song %i: %i\n", sub, size_header + size_instruments + size_song[sub]);
			}
		}
	}
	else
	{
		clear_packed_patterns();
		clear_instruments();

		printf("Input format: TextExporter plug-in\n");

		parse_instruments_old();

		clear_song();
		parse_song_old();
		song_cleanup_instrument_numbers();
		envelopes_cleanup();

		if (outtype != OUT_CA65 && outtype != OUT_LLVM) strcat(outname, ".asm"); else strcat(outname, ".s");

		output_open(outname);

		clear_packed_patterns();

		size_header = output_header(songName, -1);
		size_instruments = output_instruments();
		size_song[0] = process_and_output_song(0);

		output_close();

		size_total = size_header + size_instruments;

		printf("Header:     %i\n", size_header);
		printf("Instrument: %i\n", size_instruments);
		printf("Song data %i: %i\n", i, size_song[0]);
		size_total += size_song[0];

		printf("\nTotal data size: %i bytes\n", size_total);
	}

	text_close();

	if (dpcm_size)//save samples
	{
		file = fopen(dpcmname, "wb");
		fwrite(dpcm, dpcm_size, 1, file);
		fclose(file);
	}

	//song_text_dump(song_original);

	if (dpcm_size < 0)
	{
		printf("\nNo DPCM samples\n");
	}
	else
	{
		printf("\nDPCM samples: %i bytes\n", dpcm_size);
	}

	return 0;
}


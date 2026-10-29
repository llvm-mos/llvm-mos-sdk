#include <lynx.h>

#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_W (160)
#define SCREEN_H (102)

#define SPR_W (8)
#define SPR_H (8)
#define SPR_MAX (64)

const unsigned char sprite[] = {
    0x03, 0xB8, 0xC0, 0x03, 0xB9, 0xE0, 0x03, 0xBB, 0xF0,
    0x03, 0x3C, 0x00, 0x03, 0x3C, 0x00, 0x03, 0xBB, 0xF0,
    0x03, 0xB9, 0xE0, 0x03, 0xB8, 0xC0, 0x00,
};

// SFX produced in "Chipper" format
const unsigned char sfx[] = {
    0x84, 0x00, 0x00, 0x01, 0x28, 0x00, // SET_INSTR
    0x85, 0x6F, 0x80, 0x3F,             // PLAY
    0x85, 0x7F, 0x80, 0x3F,             // PLAY
    0x85, 0x8F, 0x80, 0x3F,             // PLAY
    0x85, 0x7F, 0x80, 0x3F,             // PLAY
    0x85, 0x6F, 0x80, 0x3F,             // PLAY
    0x85, 0x6F, 0x80, 0x3F,             // PLAY
    0x85, 0x6F, 0x80, 0x3F,             // PLAY
    0x00                                // STOP
};

typedef struct SPRITE {
  SCB_REHV_PAL scb;
  signed char hv;
  signed char vv;
} SPRITE;

SET_CART_INFO(BLOCKSIZE_256K, "My Cart                        ",
              "My Mfr         ", 1, 0);

unsigned short lastJoy = 0;
unsigned char refresh = 0;
unsigned char sprctl0 = 0;
unsigned char stats = 1;
unsigned char count = 0;
SPRITE sprites[64];

void segmentTest();
void segmentTest2();
char *itoa(int value, char *str);

void setup_sprites() {
  for (unsigned char i = 0; i < SPR_MAX; i++) {
    sprites[i].scb.sprctl1 = SKIP;

    if (i == SPR_MAX - 1)
      sprites[i].scb.next = 0;
    else
      sprites[i].scb.next = (char *)&sprites[i + 1];
  }
}

void add_sprite() {
  if (count == SPR_MAX)
    return;

  SPRITE *spr = &sprites[count];

  sprites[count].scb.sprctl0 = BPP_1 | (sprctl0 % 8);
  sprites[count].scb.sprctl1 = PACKED | REHV;
  sprites[count].scb.sprcoll = 0;
  sprites[count].scb.data = (unsigned char *)sprite;
  sprites[count].scb.hpos = (rand() % 150);
  sprites[count].scb.vpos = (rand() % 92);
  sprites[count].scb.hsize = 0x0100;
  sprites[count].scb.vsize = 0x0100;
  sprites[count].scb.penpal[0] = (rand() % 14) + 1;
  sprites[count].hv = 1;
  sprites[count].vv = 1;

  ++count;
}

void remove_sprite() {
  if (count == 1)
    return;

  --count;
  sprites[count].scb.sprctl1 = SKIP;
}

void change_sprites() {
  for (unsigned char i = 0; i < SPR_MAX; i++) {
    sprites[i].scb.sprctl0 = BPP_1 | (sprctl0 % 8);
  }
}

void handle_input(unsigned short joy) {
  if (JOY_UP(joy) && !JOY_UP(lastJoy)) {
    add_sprite();
  }

  if (JOY_DOWN(joy) && !JOY_DOWN(lastJoy)) {
    remove_sprite();
  }

  if (JOY_RIGHT(joy) && !JOY_RIGHT(lastJoy)) {
    unsigned char i;
    for (i = 0; i < 5; i++) {
      add_sprite();
    }
  } else if (JOY_LEFT(joy) && !JOY_LEFT(lastJoy)) {
    unsigned char i;
    for (i = 0; i < 5; i++) {
      remove_sprite();
    }
  }

  if (JOY_BTN_A(joy) && !JOY_BTN_A(lastJoy)) {
    ++sprctl0;
    change_sprites();
    segmentTest();
  }

  if (JOY_BTN_B(joy) && !JOY_BTN_B(lastJoy)) {
    ++refresh;
    switch (refresh % 3) {
    case 0:
      lynx_video_setframerate(50);
      break;
    case 1:
      lynx_video_setframerate(60);
      break;
    case 2:
      lynx_video_setframerate(75);
      break;
    }
  }

  if (JOY_BTN_FLIP(joy) && !JOY_BTN_FLIP(lastJoy)) {
    lynx_video_flip();
  }

  if (JOY_BTN_OPT1(joy) && !JOY_BTN_OPT1(lastJoy)) {
    lynx_cart_load(2);
    segmentTest2();
    // stats = !stats;
  }

  if (JOY_BTN_OPT2(joy) && !JOY_BTN_OPT2(lastJoy)) {
    lynx_cart_load(1);
    segmentTest();

    lynx_audio_play(3, sfx);
  }

  lastJoy = joy;
}

int main() {
  lynx_video_init();
  lynx_video_setframerate(60);
  asm("cli");
  while (lynx_video_busy()) {
  }

  lynx_audio_init();
  lynx_video_setcolor(COLOR_BLUE);

  lynx_clock_init();

  setup_sprites();
  add_sprite();

  while (true) {
    unsigned short joy = lynx_joy_read();

    handle_input(joy);

    if (!lynx_video_busy()) {
      lynx_video_clear();

      for (unsigned char i = 0; i < SPR_MAX; i++) {
        if (sprites[i].scb.hpos == SCREEN_W - SPR_W)
          sprites[i].hv = -1;
        else if (sprites[i].scb.hpos == 0)
          sprites[i].hv = 1;

        if (sprites[i].scb.vpos == SCREEN_H - SPR_H)
          sprites[i].vv = -1;
        else if (sprites[i].scb.vpos == 0)
          sprites[i].vv = 1;

        sprites[i].scb.hpos += sprites[i].hv;
        sprites[i].scb.vpos += sprites[i].vv;

        if (sprites[i].scb.next == 0)
          break;
      }

      lynx_video_sprite(&sprites[0]);

      if (stats) {
        switch (refresh % 3) {
        case 0:
          lynx_video_outtextxy(130, 0, "50");
          break;
        case 1:
          lynx_video_outtextxy(130, 0, "60");
          break;
        case 2:
          lynx_video_outtextxy(130, 0, "75");
          break;
        }

        switch (sprctl0 % 8) {
        case 0:
          lynx_video_outtextxy(0, 0, "BACKGROUND");
          break;
        case 1:
          lynx_video_outtextxy(0, 0, "BACKNONCOLL");
          break;
        case 2:
          lynx_video_outtextxy(0, 0, "BSHADOW");
          break;
        case 3:
          lynx_video_outtextxy(0, 0, "BOUNDARY");
          break;
        case 4:
          lynx_video_outtextxy(0, 0, "NORMAL");
          break;
        case 5:
          lynx_video_outtextxy(0, 0, "NONCOLL");
          break;
        case 6:
          lynx_video_outtextxy(0, 0, "XOR");
          break;
        case 7:
          lynx_video_outtextxy(0, 0, "SHADOW");
          break;
        }
      }

      static char buff[10];
      unsigned long ticks = lynx_clock_getticks();
      itoa(ticks, buff);
      lynx_video_outtextxy(0, 10, buff);

      lynx_video_updatedisplay();
    }
  }
}

START_SEGMENT(1)

__attribute__((used, noinline)) void segmentTest() {
  lynx_video_setcolor(COLOR_RED);
}

START_SEGMENT_AT(2, 0x400)

__attribute__((used, noinline)) void segmentTest2() {
  lynx_video_setcolor(COLOR_WHITE);
}

char *itoa(int value, char *str) {
  char *p = str;
  int is_negative = 0;

  if (value == 0) {
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  if (value < 0) {
    is_negative = 1;
    value = -value;
  }

  while (value > 0) {
    *p++ = (value % 10) + '0';
    value /= 10;
  }

  if (is_negative)
    *p++ = '-';

  *p = '\0';

  // reverse string
  for (char *start = str, *end = p - 1; start < end; start++, end--) {
    char temp = *start;
    *start = *end;
    *end = temp;
  }

  return str;
}
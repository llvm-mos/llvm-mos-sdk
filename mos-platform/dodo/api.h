#ifndef _API_H
#define _API_H

#ifdef __cplusplus
extern "C" {
#endif

// Specify version compiled against. Semantic versioning enforcement takes place
// in CHECK_VERSION
#define MAJOR 1
#define MINOR 1
#define REVISION 0

#define byte unsigned char

/*
 * Parameter	Type	Description
 * sprite	*byte	pointer to the sprite image data
 * x	byte	x coordinate
 * y	byte	y coordinate
 * w	byte	width of sprite
 * h	byte	height of sprite, must be multiple of 8
 * f	byte	boolean that specifies whether or not to flip horizontally
 * m	mode	drawing mode, see below
 */
__attribute__((leaf)) void DRAW_SPRITE(byte *sprite, byte x, byte y, byte w,
                                       byte h, byte f, byte m);
/* normal, replaces everything underneath the sprite */
#define DRAW_NOP 0x0
/* logical OR, fastest mode */
#define DRAW_OR 0x1
/* logical AND */
#define DRAW_AND 0x2
/* logical XOR */
#define DRAW_XOR 0x4

/* Push video memory to the OLED (expensive) */
__attribute__((leaf)) void DISPLAY();

/*
Erases the rectangular portiion of the screen defined by the parameters. Note
that background graphics will be erased as well.

Parameter	Type	Description
x	byte	x coordinate
y	byte	y coordinate
w	byte	width
h	byte	height, must be multiple of 8
*/
__attribute__((leaf)) void CLEAR_SPRITE(byte x, byte y, byte w, byte h);

/*
Sets a pixel to a specific color
Parameter	Type	Description
x	byte	x coordinate
y	byte	y coordinate
c	byte	color, 0 for black, 1 for white
*/
__attribute__((leaf)) void SET_PIXEL(byte x, byte y, byte c);

/*
Bresenham line algorithm

Parameter	Type	Description
x0	byte	x coordinate of first point
y0	byte	y coordinate of first point
x1	byte	x coordinate of second point
y1	byte	y coordinate of second point
c	byte	color, 0 for black, 1 for white
Note: Computationally expensive, it is recommended to draw lines sparingly.
*/
__attribute__((leaf)) void DRAW_LINE(byte x0, byte y0, byte x1, byte y1,
                                     byte c);

__attribute__((leaf)) void DELAY_MS(byte delay);
__attribute__((leaf)) void LED_ON();
__attribute__((leaf)) void LED_OFF();

/* Waits for an interrupt to fire. WAIT() should be called at the end of the
 * game loop in order to synchronize the frame rate to a consistent 20 FPS.  */
__attribute__((leaf)) void WAIT();

__attribute__((leaf)) void LOAD_MUSIC(byte *music);
__attribute__((leaf)) void PLAY_EFFECT(byte *effect);
__attribute__((leaf)) void PLAY_EFFECT_ONCE(byte *effect);
__attribute__((leaf)) void SPI_ENABLE();
__attribute__((leaf)) void SPI_DISABLE();
__attribute__((leaf)) void SPI_WRITE(byte v);

/* Clear the graphics in video memory */
__attribute__((leaf)) void CLEAR();

/*
Copying the background back and forth between video memory and a buffer is
useful for games with background graphics.  This technique would be used
instead of calling CLEAR_SPRITE().  Typically a game should copy the
background where a sprite will be drawn, draw the sprite, call DISPLAY() to
show the graphics, and then erase the sprite by copying the buffer back into
video memory.

The buffer needs to be a page taller than the sprite.  For instance, if the
sprite is 24x16 pixels (2 pages tall, 48 total bytes).  The buffer needs to
be 24*24 pixels (3 pages tall, 72 total bytes)

Parameter	Type	Description
data	*byte	pointer to byte array
x	byte	x coordinate
y	byte	y coordinate
w	byte	width
h	byte	height
dir	byte	direction, 0 = vmem -> buffer, 1 = buffer -> vmem
*/
__attribute__((leaf)) void COPY_BACKGROUND(byte *data, byte x, byte y, byte w,
                                           byte h, byte dir);

__attribute__((leaf)) void DRAW_STRING(const char *text);
__attribute__((leaf)) void SET_CURSOR(byte row, byte col);

/* Returns a byte that is packed with the button state. For each bit that is
 * unset the corresponding button is pushed.
 * Bit Position	Mask	Button
 * 1	1	up
 * 2	2	down
 * 3	4	left
 * 4	8	right
 * 5	16	a
 * 6	32	b
 */
__attribute__((leaf)) byte READ_BUTTONS();

__attribute__((leaf)) void GET_PIXEL(byte x, byte y);

__attribute__((leaf)) void GET_VERSION(byte *p);
__attribute__((leaf)) void CHECK_VERSION(byte major, byte minor, byte revision);

__attribute__((leaf)) void LOAD_PERSISTENT(byte *buffer);
__attribute__((leaf)) void SAVE_PERSISTENT(byte *buffer);

// This will spin forever if there is a version mismatch
#define api_init() CHECK_VERSION(MAJOR, MINOR, REVISION)

#ifdef __cplusplus
} // extern "C"
#endif

#endif

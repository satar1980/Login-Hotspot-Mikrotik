#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// SSD1306 6x8 font data
const uint8_t ssd1306xled_font6x8[] = {
    0x00, 0x06, 0x08, 0x20,
    // Space to '~' (95 characters, each 6 bytes)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
    0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
    0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
    0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
    0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
    0x00, 0x23, 0x13, 0x08, 0x64, 0x62, // %
    0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
    0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
    0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
    0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
    0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
    0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
    0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
    0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
    0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
    0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
    0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
    0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
    0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
    0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
    0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
    0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
    0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
    0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
    0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
    0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
    0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
    0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
    0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?
    0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
    0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
    0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
    0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
    0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
    0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
    0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
    0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
    0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
    0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
    0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O
    0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
    0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
    0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
    0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
    0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
    0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
    0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
    0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
    0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
    0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
    0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
    0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
    0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
    0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
    0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x00, 0x01, 0x02, 0x04, 0x00, // '
    0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
    0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
    0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
    0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
    0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
    0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
    0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
    0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
    0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
    0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
    0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
    0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
    0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
    0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o
    0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
    0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
    0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
    0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
    0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
    0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
    0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
    0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
    0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
    0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
    0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
    0x00, 0x00, 0x08, 0x77, 0x00, 0x00, // {
    0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, // |
    0x00, 0x00, 0x77, 0x08, 0x00, 0x00, // }
    0x00, 0x10, 0x08, 0x10, 0x08, 0x00, // ~
};

// String buffer
typedef struct {
    char* data;
    size_t size;
    size_t capacity;
} StringBuffer;

// Framebuffer structure
typedef struct {
    Uint16* pixels;
    int width;
    int height;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Window* window;
} Framebuffer16;

// HTMLElement types
typedef enum {
    ELEMENT_NONE,
    ELEMENT_BUTTON,
    ELEMENT_INPUT,
    ELEMENT_ANCHOR,
    ELEMENT_FORM
} HTMLElementType;

// Clickable element structure
typedef struct {
    HTMLElementType type;
    char id[64];
    char text[128];
    char action[512];
    char name[64];
    char value[128];
    int x, y, w, h;
    int active;
    int visible;
} ClickableElement;

// Browser structure
typedef struct {
    char* url;
    char* html_content;
    char* login_url;
    char* salt_prefix;
    char* salt_suffix;
    int scroll_y;
    int loading;
    int logged_in;
    int login_attempted;
    CURL* curl;
    ClickableElement* clickable_elements;
    int num_elements;
    int elements_capacity;
    char last_error[256];
} Browser;

// MD5 context and functions
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    uint8_t buffer[64];
} MD5_CTX;

/* Constants for MD5 transform routine. */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations */
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
    (a) += I((b), (c), (d)) + (x) + (uint32_t)(ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b); \
}

/* Encodes input (uint32_t) into output (uint8_t) in little-endian order */
static void encode(uint8_t *output, uint32_t *input, size_t len) {
    size_t i, j;
    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = (uint8_t)(input[i] & 0xff);
        output[j+1] = (uint8_t)((input[i] >> 8) & 0xff);
        output[j+2] = (uint8_t)((input[i] >> 16) & 0xff);
        output[j+3] = (uint8_t)((input[i] >> 24) & 0xff);
    }
}

/* Decodes input (uint8_t) into output (uint32_t) in little-endian order */
static void decode(uint32_t *output, const uint8_t *input, size_t len) {
    size_t i, j;
    for (i = 0, j = 0; j < len; i++, j += 4) {
        output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j+1]) << 8) |
                    (((uint32_t)input[j+2]) << 16) | (((uint32_t)input[j+3]) << 24);
    }
}

/* MD5 initialization */
void MD5Init(MD5_CTX *context) {
    context->count[0] = context->count[1] = 0;
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
}

/* MD5 block update operation */
void MD5Update(MD5_CTX *context, const uint8_t *input, size_t inputLen) {
    size_t i, index, partLen;
    
    index = (size_t)((context->count[0] >> 3) & 0x3F);
    
    if ((context->count[0] += ((uint32_t)inputLen << 3)) < ((uint32_t)inputLen << 3))
        context->count[1]++;
    context->count[1] += ((uint32_t)inputLen >> 29);
    
    partLen = 64 - index;
    
    if (inputLen >= partLen) {
        memcpy(&context->buffer[index], input, partLen);
        MD5Transform(context->state, context->buffer);
        
        for (i = partLen; i + 63 < inputLen; i += 64)
            MD5Transform(context->state, &input[i]);
        
        index = 0;
    } else {
        i = 0;
    }
    
    memcpy(&context->buffer[index], &input[i], inputLen - i);
}

/* MD5 finalization */
void MD5Final(uint8_t digest[16], MD5_CTX *context) {
    uint8_t bits[8];
    size_t index, padLen;
    static uint8_t PADDING[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    
    encode(bits, context->count, 8);
    
    index = (size_t)((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5Update(context, PADDING, padLen);
    MD5Update(context, bits, 8);
    
    encode(digest, context->state, 16);
    
    memset(context, 0, sizeof(*context));
}

/* MD5 basic transformation. Transforms state based on block. */
void MD5Transform(uint32_t state[4], const uint8_t block[64]) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    
    decode(x, block, 64);
    
    /* Round 1 */
    FF(a, b, c, d, x[ 0], S11, 0xd76aa478);
    FF(d, a, b, c, x[ 1], S12, 0xe8c7b756);
    FF(c, d, a, b, x[ 2], S13, 0x242070db);
    FF(b, c, d, a, x[ 3], S14, 0xc1bdceee);
    FF(a, b, c, d, x[ 4], S11, 0xf57c0faf);
    FF(d, a, b, c, x[ 5], S12, 0x4787c62a);
    FF(c, d, a, b, x[ 6], S13, 0xa8304613);
    FF(b, c, d, a, x[ 7], S14, 0xfd469501);
    FF(a, b, c, d, x[ 8], S11, 0x698098d8);
    FF(d, a, b, c, x[ 9], S12, 0x8b44f7af);
    FF(c, d, a, b, x[10], S13, 0xffff5bb1);
    FF(b, c, d, a, x[11], S14, 0x895cd7be);
    FF(a, b, c, d, x[12], S11, 0x6b901122);
    FF(d, a, b, c, x[13], S12, 0xfd987193);
    FF(c, d, a, b, x[14], S13, 0xa679438e);
    FF(b, c, d, a, x[15], S14, 0x49b40821);
    
    /* Round 2 */
    GG(a, b, c, d, x[ 1], S21, 0xf61e2562);
    GG(d, a, b, c, x[ 6], S22, 0xc040b340);
    GG(c, d, a, b, x[11], S23, 0x265e5a51);
    GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
    GG(a, b, c, d, x[ 5], S21, 0xd62f105d);
    GG(d, a, b, c, x[10], S22, 0x02441453);
    GG(c, d, a, b, x[15], S23, 0xd8a1e681);
    GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
    GG(a, b, c, d, x[ 9], S21, 0x21e1cde6);
    GG(d, a, b, c, x[14], S22, 0xc33707d6);
    GG(c, d, a, b, x[ 3], S23, 0xf4d50d87);
    GG(b, c, d, a, x[ 8], S24, 0x455a14ed);
    GG(a, b, c, d, x[13], S21, 0xa9e3e905);
    GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8);
    GG(c, d, a, b, x[ 7], S23, 0x676f02d9);
    GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);
    
    /* Round 3 */
    HH(a, b, c, d, x[ 5], S31, 0xfffa3942);
    HH(d, a, b, c, x[ 8], S32, 0x8771f681);
    HH(c, d, a, b, x[11], S33, 0x6d9d6122);
    HH(b, c, d, a, x[14], S34, 0xfde5380c);
    HH(a, b, c, d, x[ 1], S31, 0xa4beea44);
    HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9);
    HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60);
    HH(b, c, d, a, x[10], S34, 0xbebfbc70);
    HH(a, b, c, d, x[13], S31, 0x289b7ec6);
    HH(d, a, b, c, x[ 0], S32, 0xeaa127fa);
    HH(c, d, a, b, x[ 3], S33, 0xd4ef3085);
    HH(b, c, d, a, x[ 6], S34, 0x04881d05);
    HH(a, b, c, d, x[ 9], S31, 0xd9d4d039);
    HH(d, a, b, c, x[12], S32, 0xe6db99e5);
    HH(c, d, a, b, x[15], S33, 0x1fa27cf8);
    HH(b, c, d, a, x[ 2], S34, 0xc4ac5665);
    
    /* Round 4 */
    II(a, b, c, d, x[ 0], S41, 0xf4292244);
    II(d, a, b, c, x[ 7], S42, 0x432aff97);
    II(c, d, a, b, x[14], S43, 0xab9423a7);
    II(b, c, d, a, x[ 5], S44, 0xfc93a039);
    II(a, b, c, d, x[12], S41, 0x655b59c3);
    II(d, a, b, c, x[ 3], S42, 0x8f0ccc92);
    II(c, d, a, b, x[10], S43, 0xffeff47d);
    II(b, c, d, a, x[ 1], S44, 0x85845dd1);
    II(a, b, c, d, x[ 8], S41, 0x6fa87e4f);
    II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
    II(c, d, a, b, x[ 6], S43, 0xa3014314);
    II(b, c, d, a, x[13], S44, 0x4e0811a1);
    II(a, b, c, d, x[ 4], S41, 0xf7537e82);
    II(d, a, b, c, x[11], S42, 0xbd3af235);
    II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb);
    II(b, c, d, a, x[ 9], S44, 0xeb86d391);
    
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

/* Main MD5 function - returns hex string */
char* MD5String(const char* input) {
    MD5_CTX ctx;
    uint8_t digest[16];
    
    MD5Init(&ctx);
    MD5Update(&ctx, (const uint8_t*)input, strlen(input));
    MD5Final(digest, &ctx);
    
    char* output = malloc(33);
    for (int i = 0; i < 16; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
    output[32] = '\0';
    
    return output;
}

// String buffer functions
StringBuffer* sb_create() {
    StringBuffer* sb = malloc(sizeof(StringBuffer));
    sb->capacity = 4096;
    sb->data = malloc(sb->capacity);
    sb->size = 0;
    sb->data[0] = '\0';
    return sb;
}

void sb_append(StringBuffer* sb, const char* str) {
    size_t len = strlen(str);
    if (sb->size + len + 1 > sb->capacity) {
        sb->capacity = (sb->size + len + 1) * 2;
        sb->data = realloc(sb->data, sb->capacity);
    }
    strcpy(sb->data + sb->size, str);
    sb->size += len;
}

void sb_append_char(StringBuffer* sb, char c) {
    char str[2] = {c, '\0'};
    sb_append(sb, str);
}

void sb_free(StringBuffer* sb) {
    free(sb->data);
    free(sb);
}

// Color conversion
Uint16 rgb565(Uint8 r, Uint8 g, Uint8 b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

// Framebuffer functions
Framebuffer16* init_framebuffer(SDL_Window* window, SDL_Renderer* renderer, int width, int height) {
    Framebuffer16* fb = (Framebuffer16*)malloc(sizeof(Framebuffer16));
    fb->pixels = (Uint16*)calloc(width * height, sizeof(Uint16));
    fb->width = width;
    fb->height = height;
    fb->renderer = renderer;
    fb->window = window;
    fb->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, 
                                    SDL_TEXTUREACCESS_STREAMING, width, height);
    return fb;
}

void fb_clear(Framebuffer16* fb, Uint16 color) {
    for (int i = 0; i < fb->width * fb->height; i++) {
        fb->pixels[i] = color;
    }
}

void fb_pixel(Framebuffer16* fb, int x, int y, Uint16 color) {
    if (x >= 0 && x < fb->width && y >= 0 && y < fb->height) {
        fb->pixels[y * fb->width + x] = color;
    }
}

void fb_rect(Framebuffer16* fb, int x, int y, int w, int h, Uint16 color) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            fb_pixel(fb, x + i, y + j, color);
        }
    }
}

void fb_rect_border(Framebuffer16* fb, int x, int y, int w, int h, Uint16 color) {
    for (int i = 0; i < w; i++) {
        fb_pixel(fb, x + i, y, color);
        fb_pixel(fb, x + i, y + h - 1, color);
    }
    for (int i = 0; i < h; i++) {
        fb_pixel(fb, x, y + i, color);
        fb_pixel(fb, x + w - 1, y + i, color);
    }
}

void fb_draw_char(Framebuffer16* fb, int x, int y, char c, Uint16 color) {
    if (c < 32 || c > 126) c = 32;
    int font_width = ssd1306xled_font6x8[1];
    int font_height = ssd1306xled_font6x8[2];
    int first_char = ssd1306xled_font6x8[3];
    int char_index = (c - first_char) * font_width;
    int font_start = 4;
    
    for (int col = 0; col < font_width; col++) {
        uint8_t column_bits = ssd1306xled_font6x8[font_start + char_index + col];
        for (int row = 0; row < font_height; row++) {
            if (column_bits & (1 << row)) {
                fb_pixel(fb, x + col, y + row, color);
            }
        }
    }
}

void fb_text(Framebuffer16* fb, int x, int y, const char* text, Uint16 color) {
    int font_width = ssd1306xled_font6x8[1];
    int font_height = ssd1306xled_font6x8[2];
    int cur_x = x;
    int cur_y = y;
    
    for (const char* p = text; *p; p++) {
        if (*p == '\n') {
            cur_x = x;
            cur_y += font_height + 2;
        } else {
            fb_draw_char(fb, cur_x, cur_y, *p, color);
            cur_x += font_width + 1;
            if (cur_x > fb->width - font_width - x) {
                cur_x = x;
                cur_y += font_height + 2;
            }
        }
    }
}

void fb_present(Framebuffer16* fb) {
    SDL_UpdateTexture(fb->texture, NULL, fb->pixels, fb->width * sizeof(Uint16));
    SDL_RenderClear(fb->renderer);
    SDL_RenderCopy(fb->renderer, fb->texture, NULL, NULL);
    SDL_RenderPresent(fb->renderer);
}

// MD5 hash function like MikroTik
char* mikrotik_md5_hash(const char* password, const char* salt_prefix, const char* salt_suffix) {
    size_t total_len = strlen(salt_prefix) + strlen(password) + strlen(salt_suffix);
    char* input = malloc(total_len + 1);
    strcpy(input, salt_prefix);
    strcat(input, password);
    strcat(input, salt_suffix);
    
    char* hash = MD5String(input);
    free(input);
    
    return hash;
}

// Extract salt from MikroTik HTML
void extract_salt_from_html(const char* html, char** salt_prefix, char** salt_suffix) {
    *salt_prefix = NULL;
    *salt_suffix = NULL;
    
    const char* md5_pattern = strstr(html, "hexMD5('");
    if (!md5_pattern) {
        md5_pattern = strstr(html, "hexMD5(\"");
        if (!md5_pattern) return;
        md5_pattern += 7;
    } else {
        md5_pattern += 8;
    }
    
    const char* prefix_end = strstr(md5_pattern, "' + document.login.password.value + '");
    if (!prefix_end) {
        prefix_end = strstr(md5_pattern, "\" + document.login.password.value + \"");
        if (!prefix_end) return;
    }
    
    int prefix_len = prefix_end - md5_pattern;
    *salt_prefix = malloc(prefix_len + 1);
    strncpy(*salt_prefix, md5_pattern, prefix_len);
    (*salt_prefix)[prefix_len] = '\0';
    
    const char* suffix_start = prefix_end;
    if (strstr(md5_pattern, "' + document.login.password.value + '")) {
        suffix_start += strlen("' + document.login.password.value + '");
    } else {
        suffix_start += strlen("\" + document.login.password.value + \"");
    }
    
    const char* suffix_end = strstr(suffix_start, "')");
    if (!suffix_end) {
        suffix_end = strstr(suffix_start, "\")");
        if (!suffix_end) {
            free(*salt_prefix);
            *salt_prefix = NULL;
            return;
        }
    }
    
    int suffix_len = suffix_end - suffix_start;
    *salt_suffix = malloc(suffix_len + 1);
    strncpy(*salt_suffix, suffix_start, suffix_len);
    (*salt_suffix)[suffix_len] = '\0';
    
    // Convert escaped octal characters
    char* converted_prefix = malloc(strlen(*salt_prefix) + 1);
    char* converted_suffix = malloc(strlen(*salt_suffix) + 1);
    int p_idx = 0, s_idx = 0;
    
    for (size_t i = 0; i < strlen(*salt_prefix); i++) {
        if ((*salt_prefix)[i] == '\\' && i + 3 < strlen(*salt_prefix)) {
            char octal[4] = {(*salt_prefix)[i+1], (*salt_prefix)[i+2], (*salt_prefix)[i+3], '\0'};
            int val = strtol(octal, NULL, 8);
            converted_prefix[p_idx++] = (char)val;
            i += 3;
        } else {
            converted_prefix[p_idx++] = (*salt_prefix)[i];
        }
    }
    converted_prefix[p_idx] = '\0';
    
    for (size_t i = 0; i < strlen(*salt_suffix); i++) {
        if ((*salt_suffix)[i] == '\\' && i + 3 < strlen(*salt_suffix)) {
            char octal[4] = {(*salt_suffix)[i+1], (*salt_suffix)[i+2], (*salt_suffix)[i+3], '\0'};
            int val = strtol(octal, NULL, 8);
            converted_suffix[s_idx++] = (char)val;
            i += 3;
        } else {
            converted_suffix[s_idx++] = (*salt_suffix)[i];
        }
    }
    converted_suffix[s_idx] = '\0';
    
    free(*salt_prefix);
    free(*salt_suffix);
    *salt_prefix = converted_prefix;
    *salt_suffix = converted_suffix;
}

// HTTP functions
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    StringBuffer* response = (StringBuffer*)userp;
    sb_append(response, (char*)contents);
    return total_size;
}

int http_get(Browser* browser, const char* url, char** response) {
    CURLcode res;
    StringBuffer* buffer = sb_create();
    
    curl_easy_setopt(browser->curl, CURLOPT_URL, url);
    curl_easy_setopt(browser->curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(browser->curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(browser->curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(browser->curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(browser->curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36");
    curl_easy_setopt(browser->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(browser->curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    // Enable cookie handling
    curl_easy_setopt(browser->curl, CURLOPT_COOKIEFILE, "mikrotik_cookies.txt");
    curl_easy_setopt(browser->curl, CURLOPT_COOKIEJAR, "mikrotik_cookies.txt");
    
    res = curl_easy_perform(browser->curl);
    
    if (res == CURLE_OK) {
        *response = strdup(buffer->data);
        printf("Loaded %s (%zu bytes)\n", url, buffer->size);
        
        // Check if logged in by looking for login form
        if (strstr(buffer->data, "name=\"password\"") == NULL &&
            strstr(buffer->data, "login") == NULL) {
            browser->logged_in = 1;
        } else {
            // If we're on status page and see login form, we're not logged in
            if (strstr(url, "status") != NULL) {
                browser->logged_in = 0;
            }
        }
    } else {
        *response = NULL;
        snprintf(browser->last_error, sizeof(browser->last_error), "Failed to fetch %s: %s", url, curl_easy_strerror(res));
        printf("%s\n", browser->last_error);
    }
    
    sb_free(buffer);
    return (res == CURLE_OK) ? 1 : 0;
}

int http_post(Browser* browser, const char* url, const char* post_data, char** response) {
    CURLcode res;
    StringBuffer* buffer = sb_create();
    
    curl_easy_setopt(browser->curl, CURLOPT_URL, url);
    curl_easy_setopt(browser->curl, CURLOPT_POSTFIELDS, post_data);
    curl_easy_setopt(browser->curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(browser->curl, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(browser->curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(browser->curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(browser->curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36");
    curl_easy_setopt(browser->curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(browser->curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    // Enable cookie handling
    curl_easy_setopt(browser->curl, CURLOPT_COOKIEFILE, "mikrotik_cookies.txt");
    curl_easy_setopt(browser->curl, CURLOPT_COOKIEJAR, "mikrotik_cookies.txt");
    
    res = curl_easy_perform(browser->curl);
    
    if (res == CURLE_OK) {
        *response = strdup(buffer->data);
        printf("POST to %s successful\n", url);
        
        // Check if login was successful
        if (strstr(buffer->data, "name=\"password\"") == NULL &&
            strstr(buffer->data, "login") == NULL) {
            browser->logged_in = 1;
            printf("Login successful! Session saved.\n");
        } else {
            browser->logged_in = 0;
        }
    } else {
        *response = NULL;
        browser->logged_in = 0;
        snprintf(browser->last_error, sizeof(browser->last_error), "POST failed: %s", curl_easy_strerror(res));
        printf("%s\n", browser->last_error);
    }
    
    sb_free(buffer);
    return (res == CURLE_OK) ? 1 : 0;
}

// Check login status by accessing status page
int check_login_status(Browser* browser) {
    if (!browser->url) return 0;
    
    char status_url[512];
    const char* base_url = browser->url;
    
    int len = strlen(base_url);
    if (base_url[len-1] == '/') {
        snprintf(status_url, sizeof(status_url), "%sstatus", base_url);
    } else {
        snprintf(status_url, sizeof(status_url), "%s/status", base_url);
    }
    
    printf("Checking login status at: %s\n", status_url);
    
    char* response = NULL;
    if (http_get(browser, status_url, &response)) {
        int logged_in = 0;
        
        if (response) {
            if (strstr(response, "password") == NULL &&
                strstr(response, "login") == NULL) {
                logged_in = 1;
                printf("Status page indicates logged in\n");
            }
            
            if (strstr(response, "uptime") || 
                strstr(response, "Uptime") ||
                strstr(response, "Interface") ||
                strstr(response, "Traffic")) {
                logged_in = 1;
                printf("Found status information - logged in\n");
            }
            
            free(response);
        }
        
        browser->logged_in = logged_in;
        return logged_in;
    }
    
    return 0;
}

// Extract login action from HTML
char* extract_login_action(const char* html) {
    const char* form_start = strstr(html, "<form");
    if (!form_start) return NULL;
    
    const char* action = strstr(form_start, "action=\"");
    if (!action) action = strstr(form_start, "action='");
    if (!action) return NULL;
    
    action += 8;
    const char* action_end = strchr(action, '"');
    if (!action_end) action_end = strchr(action, '\'');
    if (!action_end) return NULL;
    
    int len = action_end - action;
    char* result = malloc(len + 1);
    strncpy(result, action, len);
    result[len] = '\0';
    
    return result;
}

// Parse HTML and extract clickable elements
void parse_clickable_elements(const char* html, Browser* browser) {
    if (!browser->clickable_elements) {
        browser->elements_capacity = 64;
        browser->clickable_elements = malloc(browser->elements_capacity * sizeof(ClickableElement));
    }
    browser->num_elements = 0;
    
    const char* p = html;
    int in_tag = 0;
    int in_script = 0;
    int in_style = 0;
    char tag_name[64];
    int tag_idx = 0;
    char attrs[1024];
    int attr_idx = 0;
    int is_button = 0;
    int is_anchor = 0;
    
    while (*p) {
        if (*p == '<') {
            in_tag = 1;
            tag_idx = 0;
            attr_idx = 0;
            memset(tag_name, 0, sizeof(tag_name));
            memset(attrs, 0, sizeof(attrs));
            is_button = 0;
            is_anchor = 0;
            
            if (strncasecmp(p, "<script", 7) == 0) in_script = 1;
            if (strncasecmp(p, "</script", 8) == 0) in_script = 0;
            if (strncasecmp(p, "<style", 6) == 0) in_style = 1;
            if (strncasecmp(p, "</style", 7) == 0) in_style = 0;
        } else if (*p == '>') {
            in_tag = 0;
            
            if (strcmp(tag_name, "button") == 0) {
                is_button = 1;
                if (browser->num_elements < browser->elements_capacity) {
                    ClickableElement* elem = &browser->clickable_elements[browser->num_elements++];
                    elem->type = ELEMENT_BUTTON;
                    elem->active = 1;
                    elem->visible = 1;
                    elem->x = 10;
                    elem->w = 100;
                    elem->h = 20;
                    
                    char* attr_p = attrs;
                    while (*attr_p) {
                        if (strncmp(attr_p, "id=\"", 4) == 0) {
                            attr_p += 4;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 63) elem->id[i++] = *attr_p++;
                            elem->id[i] = '\0';
                        } else if (strncmp(attr_p, "name=\"", 6) == 0) {
                            attr_p += 6;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 63) elem->name[i++] = *attr_p++;
                            elem->name[i] = '\0';
                        } else if (strncmp(attr_p, "value=\"", 7) == 0) {
                            attr_p += 7;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 127) elem->value[i++] = *attr_p++;
                            elem->value[i] = '\0';
                            strcpy(elem->text, elem->value);
                        } else if (strncmp(attr_p, "onclick=\"", 9) == 0) {
                            attr_p += 9;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 511) elem->action[i++] = *attr_p++;
                            elem->action[i] = '\0';
                        }
                        while (*attr_p && *attr_p != ' ') attr_p++;
                        while (*attr_p == ' ') attr_p++;
                    }
                    if (elem->text[0] == '\0') strcpy(elem->text, "Button");
                }
            }
            
            if (strcmp(tag_name, "a") == 0) {
                is_anchor = 1;
                if (browser->num_elements < browser->elements_capacity) {
                    ClickableElement* elem = &browser->clickable_elements[browser->num_elements++];
                    elem->type = ELEMENT_ANCHOR;
                    elem->active = 1;
                    elem->visible = 1;
                    elem->x = 10;
                    elem->w = 80;
                    elem->h = 12;
                    
                    char* attr_p = attrs;
                    while (*attr_p) {
                        if (strncmp(attr_p, "href=\"", 6) == 0) {
                            attr_p += 6;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 511) elem->action[i++] = *attr_p++;
                            elem->action[i] = '\0';
                        } else if (strncmp(attr_p, "id=\"", 4) == 0) {
                            attr_p += 4;
                            int i = 0;
                            while (*attr_p && *attr_p != '"' && i < 63) elem->id[i++] = *attr_p++;
                            elem->id[i] = '\0';
                        }
                        while (*attr_p && *attr_p != ' ') attr_p++;
                        while (*attr_p == ' ') attr_p++;
                    }
                }
            }
            
            tag_idx = 0;
        } else if (in_tag && !in_script && !in_style) {
            if (*p == ' ' || *p == '\t' || *p == '\n') {
                if (tag_idx > 0 && tag_name[0] != '\0') {
                    if (attr_idx < 1023) attrs[attr_idx++] = ' ';
                }
            } else if (tag_idx < 63) {
                if (*p != ' ' && *p != '\t' && *p != '\n') {
                    tag_name[tag_idx++] = *p;
                }
                if (attr_idx < 1023) attrs[attr_idx++] = *p;
            }
        }
        
        if (is_anchor && !in_tag && !in_script && !in_style && browser->num_elements > 0) {
            ClickableElement* elem = &browser->clickable_elements[browser->num_elements - 1];
            if (elem->type == ELEMENT_ANCHOR && strlen(elem->text) < 120) {
                int len = strlen(elem->text);
                elem->text[len] = *p;
                elem->text[len+1] = '\0';
            }
        }
        
        if (is_button && !in_tag && !in_script && !in_style && browser->num_elements > 0) {
            ClickableElement* elem = &browser->clickable_elements[browser->num_elements - 1];
            if (elem->type == ELEMENT_BUTTON && strlen(elem->text) < 120 && *p != '>') {
                int len = strlen(elem->text);
                if (*p == '\n' || *p == '\r') {
                } else if (elem->text[0] == '\0' || (len > 0 && elem->text[len-1] != ' ')) {
                    elem->text[len] = *p;
                    elem->text[len+1] = '\0';
                }
            }
            if (*p == '>') is_button = 0;
        }
        
        p++;
    }
}

// Simple HTML to text parser
char* parse_html_to_text(const char* html) {
    StringBuffer* text = sb_create();
    
    int in_tag = 0;
    int in_script = 0;
    int in_style = 0;
    int line_length = 0;
    
    const char* p = html;
    while (*p) {
        if (*p == '<') {
            in_tag = 1;
            if (strncasecmp(p, "<script", 7) == 0) in_script = 1;
            if (strncasecmp(p, "</script", 8) == 0) in_script = 0;
            if (strncasecmp(p, "<style", 6) == 0) in_style = 1;
            if (strncasecmp(p, "</style", 7) == 0) in_style = 0;
        } else if (*p == '>') {
            in_tag = 0;
        } else if (!in_tag && !in_script && !in_style) {
            if (*p == '\n' || *p == '\r') {
                if (line_length > 0) {
                    sb_append_char(text, '\n');
                    line_length = 0;
                }
            } else if (*p == ' ' || *p == '\t') {
                if (line_length > 0 && text->data[text->size-1] != ' ') {
                    sb_append_char(text, ' ');
                    line_length++;
                }
            } else {
                sb_append_char(text, *p);
                line_length++;
            }
        }
        p++;
    }
    
    return text->data;
}

// Render button element
void fb_render_button(Framebuffer16* fb, ClickableElement* elem, int x_offset, int y_offset, int scroll_y) {
    int draw_y = elem->y - scroll_y + y_offset;
    if (draw_y + elem->h < 0 || draw_y > fb->height) return;
    
    int draw_x = elem->x + x_offset;
    
    fb_rect(fb, draw_x, draw_y, elem->w, elem->h, rgb565(200, 200, 200));
    fb_rect_border(fb, draw_x, draw_y, elem->w, elem->h, rgb565(100, 100, 100));
    
    int font_width = ssd1306xled_font6x8[1];
    int font_height = ssd1306xled_font6x8[2];
    int text_width = strlen(elem->text) * (font_width + 1);
    int text_x = draw_x + (elem->w - text_width) / 2;
    int text_y = draw_y + (elem->h - font_height) / 2;
    fb_text(fb, text_x, text_y, elem->text, rgb565(0, 0, 0));
}

// Render anchor/link element
void fb_render_anchor(Framebuffer16* fb, ClickableElement* elem, int x_offset, int y_offset, int scroll_y) {
    int draw_y = elem->y - scroll_y + y_offset;
    if (draw_y + elem->h < 0 || draw_y > fb->height) return;
    
    int draw_x = elem->x + x_offset;
    
    fb_text(fb, draw_x, draw_y, elem->text, rgb565(0, 0, 255));
    
    int font_width = ssd1306xled_font6x8[1];
    int text_width = strlen(elem->text) * (font_width + 1);
    for (int i = 0; i < text_width; i++) {
        fb_pixel(fb, draw_x + i, draw_y + ssd1306xled_font6x8[2] - 1, rgb565(0, 0, 255));
    }
}

// Load page
void load_page(Browser* browser, const char* url) {
    browser->loading = 1;
    browser->scroll_y = 0;
    
    char* response = NULL;
    if (http_get(browser, url, &response)) {
        free(browser->html_content);
        browser->html_content = response;
        
        char* action = extract_login_action(response);
        if (action) {
            free(browser->login_url);
            if (strstr(action, "http")) {
                browser->login_url = action;
            } else {
                browser->login_url = malloc(strlen(url) + strlen(action) + 2);
                sprintf(browser->login_url, "%s%s", url, action);
                free(action);
            }
            printf("Found login action: %s\n", browser->login_url);
        }
        
        char* prefix = NULL;
        char* suffix = NULL;
        extract_salt_from_html(response, &prefix, &suffix);
        if (prefix && suffix) {
            free(browser->salt_prefix);
            free(browser->salt_suffix);
            browser->salt_prefix = prefix;
            browser->salt_suffix = suffix;
            printf("Extracted MD5 salt\n");
        }
        
        parse_clickable_elements(response, browser);
        printf("Found %d clickable elements\n", browser->num_elements);
    }
    
    browser->loading = 0;
}

// Perform login
void perform_login(Browser* browser, const char* username, const char* password) {
    if (!browser->login_url) {
        printf("No login URL found\n");
        snprintf(browser->last_error, sizeof(browser->last_error), "No login URL found");
        return;
    }
    
    char* post_data = NULL;
    
    if (browser->salt_prefix && browser->salt_suffix) {
        char* hashed = mikrotik_md5_hash(password, browser->salt_prefix, browser->salt_suffix);
        printf("Using MD5 hash for login\n");
        post_data = malloc(strlen(username) + strlen(hashed) + 100);
        sprintf(post_data, "username=%s&password=%s", username, hashed);
        free(hashed);
    } else {
        post_data = malloc(strlen(username) + strlen(password) + 100);
        sprintf(post_data, "username=%s&password=%s", username, password);
    }
    
    browser->loading = 1;
    browser->login_attempted = 1;
    char* response = NULL;
    
    printf("Attempting login to: %s\n", browser->login_url);
    
    if (http_post(browser, browser->login_url, post_data, &response)) {
        free(browser->html_content);
        browser->html_content = response;
        
        check_login_status(browser);
        
        if (browser->logged_in) {
            printf("Login successful!\n");
            load_page(browser, browser->url);
        } else {
            snprintf(browser->last_error, sizeof(browser->last_error), "Login failed - invalid credentials");
            printf("Login failed\n");
        }
        
        parse_clickable_elements(browser->html_content, browser);
    } else {
        browser->logged_in = 0;
    }
    
    free(post_data);
    browser->loading = 0;
}

// Perform logout
void perform_logout(Browser* browser) {
    printf("Logging out...\n");
    
    char logout_url[512];
    const char* base_url = browser->url;
    
    int len = strlen(base_url);
    if (base_url[len-1] == '/') {
        snprintf(logout_url, sizeof(logout_url), "%slogout", base_url);
    } else {
        snprintf(logout_url, sizeof(logout_url), "%s/logout", base_url);
    }
    
    printf("Attempting logout at: %s\n", logout_url);
    
    char* response = NULL;
    http_get(browser, logout_url, &response);
    free(response);
    
    curl_easy_setopt(browser->curl, CURLOPT_COOKIELIST, "ALL");
    remove("mikrotik_cookies.txt");
    
    browser->logged_in = 0;
    browser->login_attempted = 0;
    load_page(browser, browser->url);
    
    printf("Logged out and cookies cleared\n");
}

// Navigate to URL
void navigate_to(Browser* browser, const char* url) {
    char new_url[512];
    
    if (strstr(url, "http")) {
        strcpy(new_url, url);
    } else if (url[0] == '/') {
        const char* host = browser->url;
        const char* colon_slash = strstr(host, "://");
        if (colon_slash) {
            colon_slash += 3;
            const char* next_slash = strchr(colon_slash, '/');
            if (next_slash) {
                int host_len = next_slash - host;
                strncpy(new_url, host, host_len);
                new_url[host_len] = '\0';
                strcat(new_url, url);
            } else {
                strcpy(new_url, host);
                if (new_url[strlen(new_url)-1] != '/') strcat(new_url, "/");
                strcat(new_url, url + 1);
            }
        } else {
            strcpy(new_url, url);
        }
    } else {
        const char* last_slash = strrchr(browser->url, '/');
        if (last_slash) {
            int base_len = last_slash - browser->url + 1;
            strncpy(new_url, browser->url, base_len);
            new_url[base_len] = '\0';
            strcat(new_url, url);
        } else {
            strcpy(new_url, url);
        }
    }
    
    free(browser->url);
    browser->url = strdup(new_url);
    load_page(browser, browser->url);
}

// Show info dialog
void show_info_dialog(Framebuffer16* fb, const char* title, const char* message) {
    int dialog_w = 400;
    int dialog_h = 150;
    int dialog_x = (fb->width - dialog_w) / 2;
    int dialog_y = (fb->height - dialog_h) / 2;
    
    fb_rect(fb, dialog_x-5, dialog_y-5, dialog_w+10, dialog_h+10, rgb565(50, 50, 50));
    fb_rect(fb, dialog_x, dialog_y, dialog_w, dialog_h, rgb565(80, 80, 80));
    fb_rect_border(fb, dialog_x, dialog_y, dialog_w, dialog_h, rgb565(200, 200, 200));
    
    fb_text(fb, dialog_x + 20, dialog_y + 20, title, rgb565(255, 255, 255));
    fb_text(fb, dialog_x + 20, dialog_y + 50, message, rgb565(200, 200, 200));
    fb_text(fb, dialog_x + 20, dialog_y + 100, "Press any key to continue", rgb565(150, 150, 150));
    
    fb_present(fb);
    
    SDL_Event event;
    int waiting = 1;
    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                waiting = 0;
                break;
            }
        }
        SDL_Delay(16);
    }
}

// Clear credentials from memory
void clear_credentials(char* buffer, int size) {
    memset(buffer, 0, size);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    int width = 1024;
    int height = 768;
    SDL_Window* window = SDL_CreateWindow("MikroTik Browser with Button Support",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    Framebuffer16* fb = init_framebuffer(window, renderer, width, height);
    
    Browser browser;
    memset(&browser, 0, sizeof(Browser));
    
    if (argc > 1) {
        browser.url = strdup(argv[1]);
    } else {
        browser.url = strdup("http://192.168.222.1/");
    }
    
    browser.curl = curl_easy_init();
    browser.loading = 0;
    browser.logged_in = 0;
    browser.login_attempted = 0;
    browser.html_content = NULL;
    browser.login_url = NULL;
    browser.salt_prefix = NULL;
    browser.salt_suffix = NULL;
    browser.clickable_elements = NULL;
    browser.num_elements = 0;
    browser.elements_capacity = 0;
    browser.last_error[0] = '\0';
    
    load_page(&browser, browser.url);
    check_login_status(&browser);
    
    int running = 1;
    SDL_Event event;
    int text_input_active = 0;
    char username_buffer[64] = "";
    char password_buffer[64] = "";
    int input_field = 0;
    int input_cursor = 0;
    
    SDL_StartTextInput();
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT && !text_input_active && !browser.loading) {
                        int click_x = event.button.x;
                        int click_y = event.button.y;
                        
                        for (int i = 0; i < browser.num_elements; i++) {
                            ClickableElement* elem = &browser.clickable_elements[i];
                            int draw_y = elem->y - browser.scroll_y + 50;
                            int draw_x = elem->x;
                            
                            if (click_x >= draw_x && click_x <= draw_x + elem->w &&
                                click_y >= draw_y && click_y <= draw_y + elem->h) {
                                
                                printf("Clicked element: %s\n", elem->text);
                                
                                if (elem->type == ELEMENT_BUTTON) {
                                    if (strcasestr(elem->text, "logout") || 
                                        strcasestr(elem->value, "logout")) {
                                        perform_logout(&browser);
                                    } else if (strcasestr(elem->text, "login") && !browser.logged_in) {
                                        text_input_active = 1;
                                        input_field = 0;
                                        clear_credentials(username_buffer, sizeof(username_buffer));
                                        clear_credentials(password_buffer, sizeof(password_buffer));
                                        input_cursor = 0;
                                    }
                                } else if (elem->type == ELEMENT_ANCHOR && elem->action[0] != '\0') {
                                    navigate_to(&browser, elem->action);
                                }
                                break;
                            }
                        }
                    }
                    break;
                
                case SDL_KEYDOWN:
                    if (text_input_active) {
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            if (input_field == 0) {
                                input_field = 1;
                                input_cursor = 0;
                                memset(password_buffer, 0, sizeof(password_buffer));
                            } else {
                                perform_login(&browser, username_buffer, password_buffer);
                                text_input_active = 0;
                                input_field = 0;
                                clear_credentials(username_buffer, sizeof(username_buffer));
                                clear_credentials(password_buffer, sizeof(password_buffer));
                                input_cursor = 0;
                            }
                        } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                            if (input_cursor > 0) {
                                if (input_field == 0) {
                                    username_buffer[--input_cursor] = '\0';
                                } else {
                                    password_buffer[--input_cursor] = '\0';
                                }
                            }
                        } else if (event.key.keysym.sym == SDLK_TAB) {
                            input_field = !input_field;
                            input_cursor = strlen(input_field == 0 ? username_buffer : password_buffer);
                        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                            text_input_active = 0;
                            input_field = 0;
                            clear_credentials(username_buffer, sizeof(username_buffer));
                            clear_credentials(password_buffer, sizeof(password_buffer));
                            input_cursor = 0;
                        }
                    } else {
                        switch (event.key.keysym.sym) {
                            case SDLK_r:
                                load_page(&browser, browser.url);
                                break;
                            case SDLK_s:
                                if (check_login_status(&browser)) {
                                    show_info_dialog(fb, "Status", "Logged in to MikroTik");
                                } else {
                                    show_info_dialog(fb, "Status", "Not logged in");
                                }
                                break;
                            case SDLK_UP:
                                browser.scroll_y -= 20;
                                if (browser.scroll_y < 0) browser.scroll_y = 0;
                                break;
                            case SDLK_DOWN:
                                browser.scroll_y += 20;
                                break;
                            case SDLK_PAGEUP:
                                browser.scroll_y -= fb->height;
                                if (browser.scroll_y < 0) browser.scroll_y = 0;
                                break;
                            case SDLK_PAGEDOWN:
                                browser.scroll_y += fb->height;
                                break;
                            case SDLK_l:
                                if (!browser.logged_in) {
                                    text_input_active = 1;
                                    input_field = 0;
                                    clear_credentials(username_buffer, sizeof(username_buffer));
                                    clear_credentials(password_buffer, sizeof(password_buffer));
                                    input_cursor = 0;
                                }
                                break;
                            case SDLK_o:
                                if (browser.logged_in) {
                                    perform_logout(&browser);
                                }
                                break;
                            case SDLK_ESCAPE:
                                running = 0;
                                break;
                        }
                    }
                    break;
                
                case SDL_TEXTINPUT:
                    if (text_input_active && input_cursor < 63) {
                        if (input_field == 0) {
                            username_buffer[input_cursor++] = event.text.text[0];
                            username_buffer[input_cursor] = '\0';
                        } else {
                            password_buffer[input_cursor++] = event.text.text[0];
                            password_buffer[input_cursor] = '\0';
                        }
                    }
                    break;
                
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        fb->width = event.window.data1;
                        fb->height = event.window.data2;
                        free(fb->pixels);
                        fb->pixels = calloc(fb->width * fb->height, sizeof(Uint16));
                        SDL_DestroyTexture(fb->texture);
                        fb->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565,
                                                        SDL_TEXTUREACCESS_STREAMING,
                                                        fb->width, fb->height);
                    }
                    break;
            }
        }
        
        fb_clear(fb, rgb565(255, 255, 255));
        
        if (browser.loading) {
            fb_text(fb, fb->width/2 - 40, fb->height/2, "Loading...", rgb565(100, 100, 100));
        } else if (browser.html_content) {
            char* display_text = parse_html_to_text(browser.html_content);
            fb_text(fb, 10, 50 - browser.scroll_y, display_text, rgb565(0, 0, 0));
            free(display_text);
            
            int y_offset = 50;
            for (int i = 0; i < browser.num_elements; i++) {
                ClickableElement* elem = &browser.clickable_elements[i];
                elem->y = y_offset + (i * 25);
                elem->x = 10;
                
                if (elem->type == ELEMENT_BUTTON) {
                    fb_render_button(fb, elem, 0, y_offset, browser.scroll_y);
                } else if (elem->type == ELEMENT_ANCHOR && elem->text[0] != '\0') {
                    fb_render_anchor(fb, elem, 0, y_offset, browser.scroll_y);
                }
            }
        } else {
            fb_text(fb, 10, 50, "Failed to load page. Press R to retry.", rgb565(255, 0, 0));
            if (browser.last_error[0]) {
                fb_text(fb, 10, 70, browser.last_error, rgb565(255, 0, 0));
            }
        }
        
        fb_rect(fb, 0, 0, fb->width, 35, rgb565(66, 133, 244));
        
        char url_display[256];
        strncpy(url_display, browser.url, 200);
        url_display[200] = '\0';
        fb_text(fb, 10, 10, url_display, rgb565(255, 255, 255));
        
        if (browser.logged_in) {
            fb_text(fb, fb->width - 90, 10, "LOGGED IN", rgb565(0, 255, 0));
        } else if (browser.login_attempted) {
            fb_text(fb, fb->width - 110, 10, "LOGIN FAILED", rgb565(255, 100, 100));
        } else {
            fb_text(fb, fb->width - 110, 10, "NOT LOGGED IN", rgb565(255, 255, 0));
        }
        
        fb_rect(fb, 0, fb->height - 30, fb->width, 30, rgb565(240, 240, 240));
        char help_text[256];
        if (browser.logged_in) {
            snprintf(help_text, sizeof(help_text), 
                     "Click:Buttons/Links | O:Logout | S:Status | R:Refresh | ↑/↓:Scroll | ESC:Exit");
        } else {
            snprintf(help_text, sizeof(help_text), 
                     "L:Login | Click:Buttons | S:Status | R:Refresh | ↑/↓:Scroll | ESC:Exit");
        }
        fb_text(fb, 10, fb->height - 22, help_text, rgb565(80, 80, 80));
        
        if (text_input_active) {
            int dialog_w = 450;
            int dialog_h = 200;
            int dialog_x = (fb->width - dialog_w) / 2;
            int dialog_y = (fb->height - dialog_h) / 2;
            
            fb_rect(fb, dialog_x-5, dialog_y-5, dialog_w+10, dialog_h+10, rgb565(50, 50, 50));
            fb_rect(fb, dialog_x, dialog_y, dialog_w, dialog_h, rgb565(80, 80, 80));
            fb_rect_border(fb, dialog_x, dialog_y, dialog_w, dialog_h, rgb565(200, 200, 200));
            
            fb_text(fb, dialog_x + 20, dialog_y + 20, "MikroTik Router Login", rgb565(255, 255, 255));
            
            if (browser.salt_prefix && browser.salt_suffix) {
                fb_text(fb, dialog_x + 20, dialog_y + 35, "MD5 Secure Login Enabled", rgb565(100, 255, 100));
            }
            
            fb_rect(fb, dialog_x + 20, dialog_y + 60, 410, 30, rgb565(255, 255, 255));
            char user_label[128];
            snprintf(user_label, sizeof(user_label), "Username: %s%s", 
                     username_buffer, (input_field == 0 && (SDL_GetTicks() / 500 % 2)) ? "_" : "");
            fb_text(fb, dialog_x + 25, dialog_y + 67, user_label, rgb565(0, 0, 0));
            
            fb_rect(fb, dialog_x + 20, dialog_y + 105, 410, 30, rgb565(255, 255, 255));
            char pass_display[128];
            int pass_len = strlen(password_buffer);
            char stars[64];
            for (int i = 0; i < pass_len && i < 63; i++) stars[i] = '*';
            stars[pass_len] = '\0';
            snprintf(pass_display, sizeof(pass_display), "Password: %s%s", 
                     stars, (input_field == 1 && (SDL_GetTicks() / 500 % 2)) ? "_" : "");
            fb_text(fb, dialog_x + 25, dialog_y + 112, pass_display, rgb565(0, 0, 0));
            
            fb_text(fb, dialog_x + 20, dialog_y + 160, "TAB:Switch | ENTER:Login | ESC:Cancel", rgb565(200, 200, 200));
        }
        
        fb_present(fb);
        SDL_Delay(16);
    }
    
    SDL_StopTextInput();
    free(browser.html_content);
    free(browser.url);
    free(browser.login_url);
    free(browser.salt_prefix);
    free(browser.salt_suffix);
    free(browser.clickable_elements);
    curl_easy_cleanup(browser.curl);
    
    free(fb->pixels);
    SDL_DestroyTexture(fb->texture);
    free(fb);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    curl_global_cleanup();
    SDL_Quit();
    
    return 0;
}

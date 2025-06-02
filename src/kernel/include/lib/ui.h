#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#define FIRMWARE_VERSION "0.6.1" // hah)

// colors
#define TFT_GREY 0x2985
#define TFT_GREY2 0x18c3
#define TFT_GREY3 0x9492
#define TFT_DARKGREY1 0x0861

#define BOOT_LVL_OK 1
#define BOOT_LVL_FAILED 0
#define BOOT_LVL_INFO 2

typedef enum Tiles
{
    TILE_EMPTY = 0, // 0
    TILE_BUTTON,    // 1
    TILE_INPUT,     // ...
    TILE_OUTPUT,
    TILE_RADIO
} Tiles;

// Exculuded from struct to C compitable
typedef struct Positions
{
    int id;
    String title;           // tile name (buttons, fields ...) for simplicity using like id
    bool status;            // status on/off 1/0
    Tiles type;             // TILE_* type
    int8_t font_size;       // font size
    int32_t xs, ys, xe, ye; // cords
} Positions;

typedef struct GridView
{
    // Specs
    int32_t screen_w; // screen width
    int32_t screen_h; // screen height
    int16_t start_h;  // start height if have status bar or other
    int16_t end_h;    // end haight if have buttom bar or other
    // Grid
    int32_t rows;      // rows
    int32_t lines;     // lines
    int32_t pos_count; // possitions cout
    // Tiles
    int32_t tile_w; // X size in pixels for item
    int32_t tile_h; // Y size in pixels for item
    // Position
    Positions *pos;

} GridView;

String handler(GridView *grid);
void constructor(GridView *grid, String title, Tiles type, int32_t font_size = 2);
void animator(int32_t c, GridView *grid);

struct compose
{
    int32_t xs, ys, xe, ye;
};
struct compose compositor(GridView *grid, String title, uint8_t font_size);
int _updater(GridView *grid, struct compose cm, bool status, String title, Tiles type,
             uint8_t font_size);

void grid_add_button(GridView *grid, String title, uint8_t font_size);
void grid_add_radio(GridView *grid, String title, uint8_t font_size);
void grid_add_input(GridView *grid, String title, uint8_t font_size);
int grid_add_output(GridView *grid, String title, uint8_t text_position, uint8_t font_size);
void grid_add_slide(GridView *grid);

bool grid_radio_read(GridView *grid, String title);

#define TEXT_POSITION_TOP_LEFT 0
#define TEXT_POSITION_CENTER 1
int grid_output_write(GridView *grid, int id, String text, uint8_t text_position, uint8_t font_size,
                      bool append);
int grid_output_read(GridView *grid, String text);

void grid_box_alert(GridView *grid, String title, String text, uint8_t position); // window

String grid_handler(GridView *grid);
GridView *grid_init(const int32_t lines, const int32_t rows);
GridView *grid_poly_init(GridView *grid, const int32_t lines, const int32_t rows);
void grid_deinit(GridView *grid);
void grid_refresh(GridView *grid);
// void grid_cat(GridView *grid1, GridView *grid2);

void _animator_button(int32_t c, GridView *grid);

#define BACK_BUTTON_SIZE 6 // delimeter for back button size aka TFT_WIDTH / BACK_BUTTON_SIZE
int bar_handler();
void status_bar(String title = "");
void bottom_bar();
void bootlog(String log, uint8_t lvl);

#endif

#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

void grid_demo(void *lp_param)
{
    //
    // Examle 1
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 1");
        bottom_bar();

        GridView *grid1 = grid_init(4, 2);
        // line 1
        constructor(grid1, "Test 1", TILE_BUTTON, 1);
        constructor(grid1, "Test 2", TILE_BUTTON, 1);
        // line 2
        constructor(grid1, "Test 3", TILE_BUTTON, 2);
        constructor(grid1, "Test 4", TILE_BUTTON, 2);
        // line 3
        constructor(grid1, "Test 5", TILE_BUTTON, 1);
        constructor(grid1, "Test 6", TILE_BUTTON, 1);
        // line 4
        constructor(grid1, "Test 7", TILE_BUTTON, 2);
        constructor(grid1, "Next", TILE_BUTTON, 2);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid1);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "Next")
                break; // break and go next

            else if (msg != "")
                status_bar(msg);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 1");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        // clear memory after use
        grid_deinit(grid1);
    }
    //
    // Examle 2
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 2");
        bottom_bar();

        GridView *grid1 = grid_init(6, 1);
        // line 1
        constructor(grid1, "Test 1", TILE_BUTTON);
        constructor(grid1, "Test 2", TILE_BUTTON);
        // line 2
        constructor(grid1, "Test 3", TILE_BUTTON);
        constructor(grid1, "Test 4", TILE_BUTTON);
        // line 3
        constructor(grid1, "Test 5", TILE_BUTTON);
        constructor(grid1, "Next", TILE_BUTTON);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid1);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "Next")
                break; // break and go next

            else if (msg != "")
                status_bar(msg);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 2");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        grid_deinit(grid1);
    }
    //
    // Examle 3
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 3");
        bottom_bar();

        GridView *grid1 = grid_init(1, 1);
        // line 1
        constructor(grid1, "Launch Attack!", TILE_BUTTON);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid1);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "Launch Attack!")
                break; // break and go next

            else if (msg != "")
                status_bar(msg);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 3");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        grid_deinit(grid1);
    }
    //
    // Examle 4
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 4");
        bottom_bar();

        GridView *grid1 = grid_init(8, 10);
        // - 1 for lat button
        for (int i = 0; i < (8 * 10) - 1; i++)
        {
            char b[4];
            sprintf(b, "%d", i);
            constructor(grid1, b, TILE_BUTTON, 1);
            delay(15);
        }
        constructor(grid1, "N", TILE_BUTTON, 1);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid1);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "N")
                break; // break and go next

            else if (msg != "")
                status_bar(msg);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 4");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        grid_deinit(grid1);
    }
    //
    // Examle 5
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 5");
        bottom_bar();

        GridView *grid1 = grid_init(5, 1);
        constructor(grid1, "Input", TILE_INPUT, 2);

        GridView *grid2 = grid_poly_init(grid1, 5, 3);

        for (int i = 0; i < (5 * 3) - 1; i++)
        {
            char b[4];
            sprintf(b, "%d", i);
            constructor(grid2, b, TILE_BUTTON, 2);
        }
        constructor(grid2, "N", TILE_BUTTON, 1);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid2);
            String input = handler(grid1);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                grid_deinit(grid2); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "N")
                break; // break and go next
            else if (input != "")
            {
                status_bar("Input Pressed!");
            }
            else if (msg != "")
                status_bar(msg);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 5");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        grid_deinit(grid1);
        grid_deinit(grid2); // dont forget clear memory
    }
    //
    // Examle 6
    //
    {
        // update and refresh screen
        screen.fillScreen(TFT_BLACK);
        status_bar("Example 6");
        bottom_bar();

        GridView *grid1 = grid_init(6, 2);
        constructor(grid1, "Previous", TILE_BUTTON, 2);
        constructor(grid1, "Second", TILE_BUTTON, 2);

        GridView *grid2 = grid_poly_init(grid1, 8, 1);
        constructor(grid2, "Attack", TILE_BUTTON, 2);

        GridView *grid3 = grid_poly_init(grid2, 1, 1);
        grid_add_output(grid3, "Output here\nYou cant use\\n character\nto output some thinks", TEXT_POSITION_TOP_LEFT, 1);

        unsigned long bar_t = 0; // basic milis exec
        while (1)
        {
            String msg = handler(grid1);
            String msg2 = handler(grid2);
            if (msg == "EXIT")
            {
                grid_deinit(grid1); // dont forget clear memory
                grid_deinit(grid2); // dont forget clear memory
                return;             // here use return to exit all and dont go next example
            }
            else if (msg == "Second")
                break; // break and go next
            else if (msg != "")
                status_bar(msg);
            else if (msg2 != "")
                status_bar(msg2);

            if (millis() - bar_t > 5000)
            {
                status_bar("Example 6");
                bottom_bar();
                bar_t = millis();
            }

            delay(50);
        }
        grid_deinit(grid1);
        grid_deinit(grid2); // dont forget clear memory
        grid_deinit(grid3);
    }
}

void app_add_grid_demo()
{
    app_add("GUI demo", "Debug", grid_demo);
}

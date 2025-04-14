#ifndef NCURSES_UI_HPP
#define NCURSES_UI_HPP

#include <ncurses.h>
#include <map>
#include <deque>
#include <string>
#include "Order.hpp"

class NCursesUI {
    public:
        static void init(){
            initscr();
            noecho();
            cbreak();
            keypad(stdscr, TRUE);
            curs_set(0);
        }
        static void shutdown(){
            endwin();
        }
        static void render(const std::map<double, std::deque<Order>>&bids, const std::map<double, std::deque<Order>>&asks, const std::deque<TradeEvent>& trades){
            clear();
            int row = 1;
            attron(A_BOLD);
            mvprintw(row++, 2, "LIVE ORDER BOOK, Press 'n' to start a new order and 'q' to quit.");
            attroff(A_BOLD);

            mvprintw(row++, 2, "Asks (SELL): ");
            for(const auto&[price, orders]: asks){
                int totalQuantity = 0;
                attron(COLOR_PAIR(1));
                mvprintw(row++, 4, "%.2f : %d", price, totalQuantity);
                attroff(COLOR_PAIR(1));
            }

            row++;
            mvprintw(row++, 2, "Bids (BUY): ");
            for(auto it = bids.rbegin(); it != bids.rend(); ++it){
                int totalQuantity = 0;
                for(const auto&o : it->second) totalQuantity += o.quantity;
                attron(COLOR_PAIR(2));
                mvprintw(row++, 4, "%.2f : %d", it->first, totalQuantity);
                attroff(COLOR_PAIR(2));
            }            
            row += 2;
            attron(A_BOLD);
            mvprintw(row++, 2, "Recent Trades: ");
            attroff(A_BOLD);
            for (const auto& trade : trades){
                attron(COLOR_PAIR(3));
                mvprintw(row++, 4, trade.toString().c_str());
                attroff(COLOR_PAIR(3));
            }

            mvprintw(row + 2, 2, "Press 'n' to place new order, 'q' to quit.");
            refresh();
        }
        static void setupColors(){
            if(has_colors()){
                start_color();
                init_pair(1, COLOR_RED, COLOR_BLACK);
                init_pair(2, COLOR_GREEN, COLOR_BLACK);
                init_pair(3, COLOR_CYAN, COLOR_BLACK);
            }
        }
};

#endif
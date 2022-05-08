#pragma once
#include <iostream>
#include "Tree.hpp"

using std::ostream; using std::string;

namespace ariel{
    class OrgChart {

        /**************************************************/
        //================== Friend Functions =============/
        /**************************************************/
        /* Input & Output Operators */
        friend ostream& operator<<(ostream& os, const OrgChart& chart);   /* Output Operator */

    private:
        Tree<string> _chart;
        void add_root(const string& root_val);
        void add_sub(const string& super, const string& sub);
        Tree<string>::level_order_iterator begin_level_order();
        Tree<string>::level_order_iterator end_level_order();
        Tree<string>::reverse_level_order_iterator begin_reverse_order();
        Tree<string>::reverse_level_order_iterator end_reverse_order();
        Tree<string>::preorder_iterator begin_preorder();
        Tree<string>::preorder_iterator end_preorder();
    };
}
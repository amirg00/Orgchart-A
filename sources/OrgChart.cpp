#include "OrgChart.hpp"

ostream& ariel::operator<<(ostream &os, const ariel::OrgChart &chart) {

}

void ariel::OrgChart::add_root(const string &root_val) {
    _chart.add_root(root_val);
}

void ariel::OrgChart::add_sub(const string &super, const string &sub) {
    _chart.add_sub(super, sub);
}

Tree<string>::level_order_iterator ariel::OrgChart::begin_level_order() {
    return Tree<string>::begin_level_order();
}

Tree<string>::level_order_iterator ariel::OrgChart::end_level_order() {
    return Tree<string>::level_order_iterator();
}

Tree<string>::reverse_level_order_iterator ariel::OrgChart::begin_reverse_order() {
    return Tree<string>::reverse_level_order_iterator();
}

Tree<string>::reverse_level_order_iterator ariel::OrgChart::end_reverse_order() {
    return Tree<string>::reverse_level_order_iterator();
}

Tree<string>::preorder_iterator ariel::OrgChart::begin_preorder() {
    return Tree<string>::preorder_iterator();
}

Tree<string>::preorder_iterator ariel::OrgChart::end_preorder() {
    return Tree<string>::preorder_iterator();
}


#include "OrgChart.hpp"


ostream& ariel::operator<<(ostream &os, const ariel::OrgChart &chart) {
    return os;
}

ariel::OrgChart& ariel::OrgChart::add_root(const string &root_val) {
    _chart.add_root(root_val);
    return *this;
}

ariel::OrgChart& ariel::OrgChart::add_sub(const string &super, const string &sub) {
    _chart.add_sub(super, sub);
    return *this;
}


Tree<string>::level_order_iterator ariel::OrgChart::begin(){
    return _chart.begin_level_order();
}

Tree<string>::level_order_iterator ariel::OrgChart::end() {
    return _chart.end_level_order();
}

Tree<string>::level_order_iterator ariel::OrgChart::begin_level_order(){
    return _chart.begin_level_order();
}

Tree<string>::level_order_iterator ariel::OrgChart::end_level_order() {
    return _chart.end_level_order();
}

Tree<string>::reverse_level_order_iterator ariel::OrgChart::begin_reverse_order() {
    return _chart.begin_reverse_order();
}

Tree<string>::reverse_level_order_iterator ariel::OrgChart::end_reverse_order() {
    return  _chart.end_reverse_order();
}

Tree<string>::preorder_iterator ariel::OrgChart::begin_preorder() {
    return  _chart.begin_preorder();
}

Tree<string>::preorder_iterator ariel::OrgChart::end_preorder() {
    return  _chart.end_preorder();
}



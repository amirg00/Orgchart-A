#include "OrgChart.hpp"
using namespace ariel;

ostream& ariel::operator<<(ostream &os, const OrgChart &chart) {
    os << chart.to_string(os);
    return os;
}

OrgChart& OrgChart::add_root(const string &root_val) {
    if (root_val.empty()){
        throw invalid_argument("You cannot add null root!");
    }
    _chart.add_root(root_val);
    return *this;
}

OrgChart& OrgChart::add_sub(const string &super, const string &sub) {
    if (super.empty() || sub.empty()){
        throw invalid_argument("Invalid super value or sub!");
    }
    _chart.add_sub(super, sub);
    return *this;
}

Tree<string>::level_order_iterator OrgChart::begin(){
    return _chart.begin_level_order();
}

Tree<string>::level_order_iterator OrgChart::end() {
    return _chart.end_level_order();
}

Tree<string>::level_order_iterator OrgChart::begin_level_order(){
    return _chart.begin_level_order();
}

Tree<string>::level_order_iterator OrgChart::end_level_order() {
    return _chart.end_level_order();
}

Tree<string>::reverse_level_order_iterator OrgChart::begin_reverse_order() {
    return _chart.begin_reverse_order();
}

Tree<string>::reverse_level_order_iterator OrgChart::end_reverse_order() {
    return  _chart.end_reverse_order();
}

Tree<string>::preorder_iterator OrgChart::begin_preorder() {
    return  _chart.begin_preorder();
}

Tree<string>::preorder_iterator OrgChart::end_preorder() {
    return  _chart.end_preorder();
}

string OrgChart::to_string(ostream& os) const {
    return _chart.getTreeVisual(os);
}

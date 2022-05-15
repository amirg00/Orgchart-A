#include "OrgChart.hpp"
using namespace ariel;

// Output function to print organization
ostream& ariel::operator<<(ostream &os, const OrgChart &chart) {
    chart.to_string(os);
    return os;
}

// Method adds a root - the root of the organization.
OrgChart& OrgChart::add_root(const string &root_val) {
    if (root_val.empty()){
        throw invalid_argument("You cannot add null root!");
    }
    _chart.add_root(root_val);
    return *this;
}

// Add sub-entity in the organization to a super entity.
// Return the reference of the organization object
// in order to be able to add additional sub-entity.
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

// Change output stream of the tree, which represents the organization hierarchy.
void OrgChart::to_string(ostream& os) const {
    _chart.getTreeVisual(os);
}

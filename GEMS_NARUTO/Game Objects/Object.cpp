#include "Object.h"
using std::cout;
FloatRect Object::get_dimensions() const {
    return object.getLocalBounds();
}

void Object::set_position(float x, float y) {
    object.setPosition(x, y);
}

Vector2f Object::get_position() {
    return object.getPosition();
}

void Object::draw(RenderWindow &window) const {
    window.draw(object);
}

void Object::set_texture(const string &image_path) {
    if(!texture.loadFromFile(image_path)){
        cout << "ERROR";
        return;
    }
    object.setTexture(texture);
}

FloatRect Object::get_bounds() const{
    return object.getGlobalBounds();
}

void Object::set_position(Vector2f new_pos) {
    object.setPosition(new_pos);
}

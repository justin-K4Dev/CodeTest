-- Define class.
Rectangle =
Class     "Rectangle"
:include  "<string>"
:include  "<sstream>"
:include  "<iostream>"
:property "double width = 0.0"
:property "double height = 0.0"
:func[[
    /* Get the surface area of the rectangle. */
    double get_area() const {
      return get_width() * get_height();
    }
  ]]  :func[[
    /* Resize rectangle by scale factor. */
    void scale(double amount = 0) {
      set_width(get_width() * amount);
      set_height(get_height() * amount);
    }
  ]]  :func[[
    /* Convert rectangle to string. */
    std::string tostring() {
      ostringstream os;
      os << "Rectangle[" << get_width() << "," << get_height() << "]";
      return os.str();
    }
  ]]

-- Define module (compilation unit).
Rectanglem = 
Module   "rectanglem"
:include "<iostream>"
:using_namespace "std"
:class(Rectangle)
:func[[
    /* entry point */
    int main() {
      Rectangle s;
      s.set_width(10);
      s.set_height(20);
      s.scale(2);
      cout << s.tostring() << " " << s.get_area() << " " << s.get_class_name() << endl;
      return 0;
    }
  ]]
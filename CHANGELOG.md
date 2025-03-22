# Changelog
This file is to be used to update the changes you made in this challenge. Please use the guide below to place new code in **Additions**, any changes to existing code in **Changes** and any bug fixes in **Fixes**. You may update version how you like.

## **Version 1.0.5**

### **Additions**
<cstdio> module added - for std::puts(str) - when you need quickly print something (like change color)
<print> module added - from std::println(str) (C++23)

---

### **Changes**
"Rogue" SetConsoleTextAttribute functions changed to SetColor
<regex> removed (not needed)
<iostream> only used for std::cin
std::cout was changed to more optimized and modern std::println (when used with formatting)
std::cout was changed to std::puts (when we only need to quickly print something)
<format> module was removed since not needed anymore
std::endl removed from MenuWeaponList

---

### **Fixes**
1.0.4 - fixed screen flickering (ClearScreen was placed in the beginning of the function, from the end)
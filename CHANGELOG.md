# Changelog
This file is to be used to update the changes you made in this challenge. Please use the guide below to place new code in **Additions**, any changes to existing code in **Changes** and any bug fixes in **Fixes**. You may update version how you like.

## **Version 1.0.4**

### **Additions**
driver is now a module
Added enum for rock, paper scissors
Added enum for colors
Added UNIX support
Added show of total number of rounds beside currernt round number
Added more colors, everything looks more tidy
Game can't be drawn, you have to 'fight' until the winner is determined - Tiebreaker

---

### **Changes**
import instead of include
<random> instead of cstdlib
round changed to 1 from 0; //number of rounds can't be 0, minimum 1
Removed input check what so ever - user can only choose what the program tells him
Removed unnecessary couts
if-else statements changed to switch
Less menus and functions 
Changed ClearScreen() to more secure and optimized

---

### **Fixes**
Fix starting round number from 0 to 1
fixed win logic
while (round <= roundLimit)
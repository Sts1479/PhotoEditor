# PhotoEditor
A little terminal application to do some operations with a photo format files

ld,load - Loading the new file of jpg format and associate with the image name  
Format: ld,load <name of the image> <path to a file of jpg format>. Example: ld img1 /Users/user1/Pictures/nat.jpg

rs,resize - Resize the image and save result in a new image  
Format: rs,resize <name of the image_old> <name of the image_new> <height> <width>. Example: rs img1 img2 800 800

blur - Blur the image and save result in a new image  
Format: blur <name of the image_old> <name of the image_new> <core size>. Example: blur img1 img2 5

s,store - Store to a new image file, that associated with the image name  
Format: s,store <name of the image> <path to a file of jpg format>. Example: s img1 /Users/user1/Pictures/nat.jpg

quit,exit,q - Exiting the program
Example of the session:

ld img1 image.jpg
blur img1 img1b 5
s img1b image2.jpg
q



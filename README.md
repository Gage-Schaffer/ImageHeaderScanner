# ImageHeaderScanner
🖥️ Welcome to my first C repo! 

Here, I have some code that iterate the header of certain image file formats and return some information. It won't go further than that, but I do have some plans to extend functionality into actually parsing the image data.

One reason that I made this is the lack of information on scanning the headers of image files. I searched for a long time for a tutorial or video, but I eventually stumbled upon libjpeg's source code which got me started.

Speaking of libjpeg, their method inspired a lot of my methods of parsing the headers. Originally, I was doing some messy malloc() things and was struggling with wasted memory and cleanly parsing the header data. Their elegent use of getc() and iterating through the header byte-by-byte was extremely smooth and inspiring. It's how I'll probably iterate files from now on!

# 🔍 Grokking Image File Information in Pure C 🔍
By making extensive use of getc() and some bit shifting, we are able to gather information on files just from the header. Currently, we can only scan BMP file headers, but I am working on JPEG header code now.

The code is fairly simple. We use getc() over and over in order to iterate each byte. By using the technical specs of each image type, we can discern how many bytes to iterate at a time and what the values actually mean.

From here, we append that data to a struct. For BMPs, the struct is BMPHeader and contains every field that the header has. For JPEGs, it will be the same philosophy: JPEGHeader with all the required fields.

### 🖱️ Why C?
I like C.

### 🖼️ What Other File Types Will There Be?
Right now, just JPEG is in the works, but I plan to expand to PNG as well.


## To-do List
Here's the immediate list of tasks:
- [x] Add BMP Header Parsing
- [ ] Add JPEG Header Parsing
- [ ] Add PNG Header Parsing

There's also some more tasks I'd like to complete (for my own personal projects):
- [ ] Parse BMP pixel data
- [ ] Parse JPEG pixel data
- [ ] Parse PNG pixel data

Once the above is complete, I want to turn these image types into ASCII art:
- [ ] Write code to transform images into ASCII art

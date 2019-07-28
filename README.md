# the-react
The React is crossplatform minimal top-down shooter, written in c, SDL, OpenGL.

# Dependencies
SDL2

# Usage
```bash
./bin/react screen_width screen_height
```

# Controls
* W - move forward
* A - strafe left
* D - strafe right
* S - strafe down
* Left, Middle, Right mouse buttons - shoot

# Resources
Resources are usual text files


# Map file format
<pre>
For example: w,100,100,0,0,1;
w - wall;
100 - x coord;
100 - y coord;
0 - red color;
0 - green color;
1 - blue color;
</pre>

<pre>
For example: e,80,25,hexenemy;
e - enemy;
80 - x coord;
25 - y coord;
hexenemy - filename with enemy options;
</pre>

<pre>
For example: b,12,32,speedup;
b - bonus;
12 - x coord;
32 - y coord;
speedup - filename with bonus options;
</pre>

<pre>
For example: f,300,0,500,100;
f - end of the level;
300 - x coord;
0 - y coord;
500 - width;
100 - height;
</pre>

<pre>
For example: p,950,150;
p - player start;
950 - x coord;
150 - y coord;
</pre>

# Enemy file format
<pre>
v,0,0,0,1,0,20,0,0,1,0,20,20,0,1,0,0,20,0,1,0;w,20;h,20;l,10;s,2;r,2;g,7;d,20;

v,x1,y1,red,green,blue,x2,y2,red,green,blue,...; - points(LINE_LOOP) to draw enemy
w,20; - width;
h,20; - height;
l,10; - enemy health;
s,2; - enemy speed;
r,2; - enemy bullet radius;
g,7; - enemy bullet speed;
d,20; - enemy shoot duration;
</pre>

# Bonus file format
<pre>
v,0,10,1,0,0,0,0,1,0,0,5,0,1,0,0,5,5,1,0,0,0,5,1,0,0,5,10,1,0,0,0,5,1,0,0;w,5;h,10;f,radiusup;d,400;a1,6;a2,10;

v,x1,y1,red,green,blue,x2,y2,red,green,blue,...; - points(LINE_LOOP) to draw bonus
w,5; - width;
h,10; - height;
f,radiusup; - name of function, which contains in bonus_func.c;
d,400; - duration of second function activate;
a1,6; - argument for first function activate;(aka data);
a2,10; - argument for second function activate(aka data);
</pre>

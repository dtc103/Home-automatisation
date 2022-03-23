// #ifndef PANEL_EFFECTS_H
// #define PANEL_EFFECTS_H

// #include <Panel.h>

// class Effect{
// public:
//     void start(){
//         this->running = true;
//     }
//     void stop(){
//         this->running = false;
//     }
//     bool is_running() const{
//         return this->running;
//     }
// private:
//     volatile bool running = false;
// };

// class Panel_Effect: public Effect{
// public:
//     Panel_Effect(Panel panel): panel{panel}, Effect(){
//     }

//     void begin(){
//         this->panel.begin();
//     }

//     void fill(unsigned int red, unsigned int green, unsigned int blue, unsigned int white = 255){
//         for (size_t i = 0; i < this->panel.get_y_length(); ++i)
//         {
//             for (size_t j = 0; j < this->panel.get_x_length(); ++j)
//             {
//                 this->panel.set_color(j, i, red, green, blue, white);
//             }
//         }
//         this->panel.render();
//     }

//     void strobe(unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time){
//         int start_time = millis();
//         bool lights_on = false;
//         long rand = random(0, max_strobe_time);
//         this->panel.clear();
//         this->panel.render();

//         while(this->is_running()){
//             if (millis() - start_time > rand)
//             {
//                 rand = random(0, max_strobe_time);
//                 start_time = millis();
//                 if (lights_on)
//                 {
//                     this->panel.clear();
//                     this->panel.render();
//                     lights_on = false;
//                 }
//                 else
//                 {
//                     this->fill(red, green, blue, max_brightness);
//                     lights_on = true;
//                 }
//             }
//         }
//     }

//     void rainbow_lane(unsigned int lane_length = 1, unsigned int velocity = 100){
//         const unsigned int max_hue = 65535;
//         const unsigned int length = this->panel.get_x_length() * this->panel.get_y_length();
//         const float interpolation_part = (1.0f / (float)(length - 1)) * max_hue;

//         bool left = true;

//         if (lane_length >= length)
//             lane_length = length;


//         for (unsigned int y = 0; y < this->panel.get_y_length(); ++y)
//         {
//             //calculate x and y pos of the individual lights
//             unsigned int x_pos = 0;
//             unsigned int y_pos = 0;
//             unsigned int y_shift = 0; //y_shift calculates the distance from the curr led y-pos to the first led y_pos
//             if (left)
//             {
//                 for (unsigned int x = 0; x < this->panel.get_x_length(); ++x)
//                 {
//                     for (unsigned int curr = this->panel.get_x_length() - 1 - x; curr < this->panel.get_x_length() - 1 - x + lane_length; ++curr)
//                     {
//                         y_shift = curr / this->panel.get_x_length();
//                         //calculate y_pos
//                         y_pos = (this->panel.get_y_length() + (y - y_shift)) % this->panel.get_y_length();
//                         //calculate x_pos
//                         if (y_shift % 2 == 0)
//                         {
//                             x_pos = curr % this->panel.get_x_length();
//                         }
//                         else
//                         {
//                             x_pos = (this->panel.get_x_length() - 1) - (curr % this->panel.get_x_length());
//                         }
//                         this->panel.set_color_HSV(x_pos, y_pos, this->panel.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
//                     }
//                     this->panel.render();
//                     delay(velocity);
//                     this->panel.clear();
//                 }
//                 left = !left;
//             }
//             else
//             {
//                 for (unsigned int x = 0; x < this->panel.get_x_length(); ++x)
//                 {
//                     //if lane_length isnt converted to int, the solution from x-lane_length will be unsigned and therefore never smaller than 0
//                     for (unsigned int curr = 0; curr < lane_length; ++curr)
//                     {
//                         y_shift = (this->panel.get_x_length() - 1 - x + curr) / this->panel.get_x_length();
//                         y_pos = (this->panel.get_y_length() + (y - y_shift)) % this->panel.get_y_length();
                        
//                         if (y_shift % 2 == 0)
//                         {
//                             x_pos = this->panel.get_x_length() - 1 - ((this->panel.get_x_length() - 1 - x + curr) % this->panel.get_x_length());
//                         }
//                         else
//                         {
//                             x_pos = (this->panel.get_x_length() - 1 - x + curr) % this->panel.get_x_length();
//                         }
//                         this->panel.set_color_HSV(x_pos, y_pos, this->panel.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
//                     }
//                     this->panel.render();
//                     delay(velocity);
//                     this->panel.clear();
//                 }
//                 left = !left;
//             }
//         }
//     }

//     void color_lane(unsigned int lane_length = 1, unsigned int red = 255, unsigned int green = 255, unsigned int blue = 255, unsigned int white = 255, unsigned int velocity = 100){
//         const unsigned int max_length = this->panel.get_x_length() * this->panel.get_y_length();

//         if (lane_length >= max_length)
//             lane_length = max_length;

//         int curr_pos_x = 0;
//         int curr_pos_y = 0;
//         bool left = false;

//         while(this->is_running()){
//             if(curr_pos_x >= this->panel.get_x_length()){
//                 curr_pos_x = this->panel.get_x_length() - 1;
//                 left = true;
//             }
//             if(curr_pos_x < 0){
//                 curr_pos_x = 0;
//                 left = false;
//             }
//             if(curr_pos_y >= this->panel.get_y_length()){
//                 curr_pos_y = 0;
//             }

//             for(int pixel = 1; pixel < lane_length; pixel++){
//                 unsigned int pixel_pos_x = 0; //calculate x pos of the individual tail lights
//                 unsigned int pixel_pos_y = 0; //calculate y pos of the individual tail lights
//                 unsigned int pixel_y_shift = 0; //pixel_y_shift calculates the distance from the curr led y-pos to the first led y_pos
                
//                 if(left){

//                 }else{
//                     pixel_y_shift = (curr_pos_x - pixel) >= 0 ? 0 : -1 * (curr_pos_x - (pixel - 1)) / (this->panel.get_x_length()) + 1;
//                     pixel_pos_y = ((curr_pos_y - (int)pixel_y_shift) + this->panel.get_y_length()) % this->panel.get_y_length();
//                     //TODO
//                     //pixel_pos_x = (pixel_y_shift % 2 == 0) ?  this->panel.get_x_length() - 1 - ((pixel % this->panel.get_x_length()) + curr_pos_x)
//                 }
//             }

            
             
//             if (left)
//             {
//                 for (unsigned int x = 0; x < this->panel.get_x_length(); ++x)
//                 {
//                     //curr refers to the current x-value of the light
//                     for (unsigned int curr = this->panel.get_x_length() - 1 - x; curr < this->panel.get_x_length() - 1 - x + lane_length; ++curr)
//                     {
//                         y_shift = curr / this->panel.get_x_length();
//                         //calculate y_pos
//                         y_pos = (this->panel.get_y_length() + (y - y_shift)) % this->panel.get_y_length();
//                         //calculate x_pos
//                         if (y_shift % 2 == 0)
//                         {
//                             x_pos = curr % this->panel.get_x_length();
//                         }
//                         else
//                         {
//                             x_pos = (this->panel.get_x_length() - 1) - (curr % this->panel.get_x_length());
//                         }
//                         this->panel.set_color(x_pos, y_pos, red, green, blue, white);
//                     }

//                     this->panel.render();
//                     delay(velocity);
//                     this->panel.clear();
//                 }
//                 left = !left;
//             }
//             else
//             {
//                 for (unsigned int x = 0; x < this->panel.get_x_length(); ++x)
//                 {
//                     //if lane_length isnt converted to int, the solution from x-lane_length will be unsigned and therefore never smaller than 0
//                     for (unsigned int curr = 0; curr < lane_length; ++curr)
//                     {
//                         y_shift = (this->panel.get_x_length() - 1 - x + curr) / this->panel.get_x_length();
//                         y_pos = (this->panel.get_y_length() + (y - y_shift)) % this->panel.get_y_length();
                        
//                         if (y_shift % 2 == 0)
//                         {
//                             x_pos = this->panel.get_x_length() - 1 - ((this->panel.get_x_length() - 1 - x + curr) % this->panel.get_x_length());
//                         }
//                         else
//                         {
//                             x_pos = (this->panel.get_x_length() - 1 - x + curr) % this->panel.get_x_length();
//                         }
//                         this->panel.set_color(x_pos, y_pos, red, green, blue, white);
//                     }

//                     this->panel.render();
//                     delay(velocity);
//                     this->panel.clear();
//                 }
//                 left = !left;
//             }
            
//         }
//     }

//     void drops(unsigned int length = 5, unsigned int red = 0, unsigned int green = 255, unsigned int blue = 0, unsigned int density = 25, unsigned int vel = 100){

//     }
// private:
//     Panel panel;

// };

// class Strip_Effect: public Effect{

// };

// #endif
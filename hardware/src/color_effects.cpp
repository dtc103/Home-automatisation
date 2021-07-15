#include "color_effects.h"
/*
//TODO: delay ersetzen durch millis
void Color_Effects_Dynamic::rainbow_lane(Panel &led_panel, unsigned int lane_length, unsigned int velocity)
{
    

}

//TODO: delay ersetzen durch millis
void Color_Effects_Dynamic::color_lane(Panel &led_panel, unsigned int lane_length, unsigned int red, unsigned int green, unsigned int blue, unsigned int white, unsigned int velocity)
{
    

}

void Color_Effects_Dynamic::drops(Panel &led_panel, unsigned int length, unsigned int red, unsigned int green, unsigned int blue, unsigned int density, unsigned int vel)
{
    int *drops[density];
    for(int i = 0; i < density; ++i){
        drops[density] = new int[2]();

        if (random(0, 99) < 10){
            drops[i][0] = random(0, led_panel.get_x_length());
            drops[i][1] = random(0, led_panel.get_y_length());
        }else{
            drops[i][0] = -1;
            drops[i][1] = 0;
        }
    }

    while(true){
        for(int drop = 0; drop < density; ++drop){
            //if the drop is valid
            if(drops[drop][0] > -1){
                for(int tail = 0; tail < length; ++tail){
                    //if the tail is valid
                    if(drops[drop][1] - tail > -1 && drops[drop][1] - tail < led_panel.get_y_length()){
                        led_panel.set_color(drops[drop][0], drops[drop][1] - tail, red, green, blue);
                    }
                }
                ++drops[drop][1];
                if(drops[drop][1] >= led_panel.get_y_length() + length){
                    drops[drop][0] = -1;
                    drops[drop][1] = 0;
                }          
            }else{
                if (random(0, 99) < 10){
                    drops[drop][0] = random(0, led_panel.get_x_length());
                    drops[drop][1] = random(0, led_panel.get_y_length());
                }
            }
        }
        led_panel.render();
    }
    
}
*/
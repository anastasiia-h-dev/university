#include <iostream>
#include <cstdlib> // rand
#include <ctime>
#include <unistd.h>

using namespace std;

bool is_in_air = false; // checking if uav is in the sky

class UAV; // forward declaration
class Pilot;



class Radio_Receiver{
    private:
        bool converted = false;

    public:
        bool is_signal_converted(){
            return converted = true;
        }

};

class Antenna{
    private:
        bool received = false;

    public:
        bool is_signal_received(){
            return received = true;
        }
};

class Telemetry{
    private:
    double GNSS, IMU, magnetometer, altitude, speed;

    public:

    void generate_data(){
        GNSS = 50.0 + (rand() % 1000) / 1000.0; 
        IMU = (rand() % 200 - 100) / 10.0;             
        magnetometer = rand() % 360;  
        altitude = 100 + rand() % 200;  
        speed = 10 + rand() % 120;                       
    }

    void send_data(){
        generate_data();

        sleep(rand()%2 + 1);
        cout << "\n\033[1;32m[Telemetry]\033[0m";
        cout << "\n  GNSS : " << GNSS;
        cout << "\n  IMU : " << IMU;
        cout << "\n  Magnetometer : " << magnetometer << " deg";
        cout << "\n  Altitude: " << altitude << " m";
        cout << "\n  Speed: " << speed << " m/s\n";
    }
};

class Camera{
    private:
    int current_zoom = 0;

    public:

    void change_zoom(){
        
        sleep(rand()%3 + 1);
        cout << "\n\033[1;33m[+] Current zoom : \033[0m" << current_zoom;
        cout << "\n\033[1;35m[*] Change to : \033[0m";
        cout << "\n\033[1;35m| 0x | 5x | 10x | 15x |\n\033[0m";
        int zoom;
        cin >> zoom;

        if(zoom != 0 && zoom != 5 && zoom != 10 && zoom != 15){
            sleep(rand()%3 + 1);
            cout << "\n\033[1;31m [!] Wrong setting\033[0m";
            return;
        }
        else if(zoom == current_zoom){
            sleep(rand()%3 + 1);
            cout << "\n\033[1;33m [!] CAMERA already works in " << zoom << "x zoom\033[0m";
        }
        else{
            current_zoom = zoom;
            sleep(rand()%3 + 1);
            cout << "\n\033[1;32m [+] ZOOM was changed to : \033[0m" << zoom;
        }
    }
};


class Servo{
    public:
        void execute_command(string command, UAV *uav);

};

class ESC{
    public:
    void execute_command(string command, UAV *uav);
};

class Flight_Controller{
public:
    void execute_command(string command, UAV* uav, Servo &servo, ESC &esc, Camera &camera, Telemetry &telemetry);
};


class Battery{
private:
    bool is_on_state = false;

public:
    void turn_on(){
        sleep(2);
        is_on_state = true;
        cout << "\n\033[1;32m[+] BATTERY was turned ON\033[0m";
    }
    void turn_off(){
        sleep(2);
        is_on_state = false;
        cout << "\n\033[1;32m[+] BATTERY was turned OFF\033[0m";
    }

    bool is_on(){
        return is_on_state;
    }
};

class Construction{
    private:
        string right_aileron, left_aileron;
        string right_elevator, left_elevator;

    public:
        
        string right_aileron_up(){
            return right_aileron = "up";
        }
  
        string right_aileron_down(){
            return right_aileron = "down";
        }
                
        string left_aileron_up(){
            return left_aileron = "up";
        }

        string left_aileron_down(){
            return left_aileron = "down";
        }

        string right_elevator_up(){
            return right_elevator = "up";
        }

        string right_elevator_down(){
            return right_elevator = "down";
        }

        string left_elevator_up(){
            return left_elevator = "up";
        }

        string left_elevator_down(){
            return left_elevator = "down";
        }
};

class Moving_system{
    Servo srv;
    ESC esc;

    private:
    bool is_catapulted = false;
    bool deployed = false;
    string motor_state = "motor not started";
    bool propellers_working = false;

    public:

    bool to_catapult(){
        is_catapulted = true;
        return is_catapulted;
    }

    bool deploy() {
        if(!is_in_air){
            sleep(1);
            cout << "\n\033[1;31m[!] Cannot deploy PARACHUTE on ground\033[0m";
            return false;
        }

        deployed = true;
        sleep(1);
        cout << "\n\033[1;32m[+] PARACHUTE deployed\033[0m";
        return true;
    }

    bool is_deployed(){
        return deployed;
    }

    bool to_start_motor(){
        motor_state = "motor is started";
        
        propellers_working = true;
        if(propellers_working == true){
            sleep(1);
            cout << "\n\033[1;32m[+] Propellers are working\033[0m";
            return true;
        }
        else{
            sleep(1);
            cout << "\n\033[1;31m[!] Propellers are not working\033[0m";
            return false;
        }
    }

};

class Cooling_System{
    public:
    void cooling(){
        if(is_in_air){
        cout << "\n\033[1;32m[+] The cooling system is working\033[0m";
        }
        else{
        cout << "\n\033[1;32m[-] The cooling system is off\033[0m";

        }
    }
};

class Avionics {
private:
    Flight_Controller fc;
    Antenna antenna;
    Radio_Receiver rr;
    Camera camera;
    Telemetry telemetry;

public:
    void process_command(string command, UAV* uav, Servo& servo, ESC& esc){
        if (antenna.is_signal_received()) {
            sleep(2);
            cout << "\n[!] ANTENNA received signal";

        if (rr.is_signal_converted()) {
            sleep(2);
            cout << "\n[!] RADIO RECEIVER converted signal";

            fc.execute_command(command, uav, servo, esc, camera, telemetry);
        }
        else {
            sleep(2);
            cout << "\n[!] RADIO RECEIVER failed";
        }
    }
    else {
            sleep(2);
        cout << "\n[!] ANTENNA didn't receive signal";
    }
    }
};

/// main class
class UAV{
    private:

    double max_speed;
    double flight_range;
    double min_flight_height;
    double weight;

    
    bool motor_started = false;
    
    Construction construction;
    Battery battery;
    Moving_system moving_system;
    Cooling_System cooling;

    Avionics avionics;
    Servo servo;
    ESC esc;

    // визначаю обʼєкт антенна, яка приймає сигнал
    // передаю сигнал на FC
    // FC передає сигнал на сервопривід або ESC або камеру або систему посадки в залежності від команди

    public:

    //constructor
    UAV(double inputMaxSpeed, double inputFlightRange, double inputMinFlightHeight, double inputWeight){
        max_speed = inputMaxSpeed;
        flight_range = inputFlightRange;
        min_flight_height = inputMinFlightHeight;
        weight = inputWeight;
    };

    void receive_command(string command){
        if(battery.is_on()){
            avionics.process_command(command, this, servo, esc);
        }
        else{
            cout << "\n\033[1;31m[!] BATTERY is OFF. Turn it ON first.\033[0m";
        }
    }

    void turnBatteryOn(){
        if(is_in_air){
            cout << "\n\033[1;33m[!] UAV is already in air\033[0m";
            return;
        }
        else if(battery.is_on()){
            cout << "\n\033[1;33m[!] BATTERY is already ON\033[0m";
        }
        else {
            battery.turn_on();
        }
    }

    void turnBatteryOff(){
        if(is_in_air){
            cout << "\n\033[1;31m[!] Operation not permitted : UAV is in air\033[0m";
            return;
        }
        else if(!battery.is_on()){
            cout << "\n\033[1;33m[!] BATTERY is already OFF\033[0m";
        }
        else{
            battery.turn_off();
        }
    }

    bool start_motor(){
        if(!battery.is_on()){
            cout << "\n\033[1;31m[!] BATTERY is OFF. Turn it ON first.\033[0m";
            return false;
        }

        if(is_in_air){
            cout << "\n\033[1;33m[!] UAV is already in air\033[0m";
            return false;
        }

        else if(moving_system.to_start_motor()){
            cout << "\n\033[1;32m[+] MOTOR was started\033[0m";
            motor_started = true;
            return true;
        }
        else{
            cout << "\n\033[1;31m[!] Failed to start motor\033[0m";
            return false;
        }
    }

    void takeoff(){

        if(is_in_air){
            cout << "\n\033[1;33m[[!] UAV is already in air\033[0m";
            cooling.cooling();
            return;
        }

        else if(battery.is_on()){
            if(motor_started){

                if(moving_system.to_catapult()){
                    sleep(3);
                    cout << "\n\033[1;32m[+] UAV was successfully launched\033[0m";
                    is_in_air = true;
                    cooling.cooling();
                    }

                    else{
                        cout << "\n\033[1;31m[!] UAV wasn't catapulted\033[0m";
                        return;
                    }
            }
            else{
                cout << "\n\033[1;31m[!] UAV wasn't launched : MOTOR didn't start\033[0m";
                return;
            }
        }
        else{
            cout << "\n\033[1;31m[!] BATTERY is OFF. Turn it ON first.\033[0m";
            return;
        }
    }

    void land(){
        if(is_in_air){
                if(!moving_system.deploy()){
                cout << "\n[!] Landing failed";
                return;
                }
                motor_started = false;
                is_in_air = false;
                cooling.cooling();
        }
        else{
            cout << "\n\033[1;31m [!] The UAV wasn't launched yet\033[0m";
            is_in_air = false;
        }
    }

    bool check_right_aileron(){ 
        if(!is_in_air){
            if(battery.is_on()){
                if((construction.right_aileron_up() != "up") || (construction.right_aileron_down() != "down")){
                    cout << "\n\033[1;31m[!] Something is wrong with the RIGHT AILERON.\033[0m";
                    return false;
                }
                else{
                    cout << "\n\033[1;32m[+] OK. RIGHT AILERON responds.\033[0m";
                    return true;
                }
            }
            else {
                cout << "\n\033[1;31m[!] The BATTERY is OFF. Turn it ON first\033[0m";
                return false;
            }
            return true;
        }

        else{
            cout << "\n\033[1;31m [!] Operation not permitted : UAV is in the process of reconnaissance\033[0m";
            return false;
        }
    }

    bool check_left_aileron(){
        if(!is_in_air){
            if(battery.is_on()){
                if((construction.left_aileron_up() != "up") || (construction.left_aileron_down() != "down")){
                    cout << "\n\033[1;31m[!] Something is wrong with the LEFT AILERON.\033[0m";
                    return false;
                }
                else{
                    cout << "\n\033[1;32m[+] OK. LEFT AILERON responds.\033[0m";
                    return true;
                }
            }
            else {
                cout << "\n\033[1;31m[!] The BATTERY is OFF. Turn it ON first\033[0m";
                return false;
            }
            //return true;
        }

        else{
            cout << "\n\033[1;31m [!] Operation not permitted : UAV is in the process of reconnaissance\033[0m";
            return false;
        }
    }

    bool check_right_elevator(){
        if(!is_in_air){
            if(battery.is_on()){
                if((construction.right_elevator_up() != "up") || (construction.right_elevator_down() != "down")){
                    cout << "\n\033[1;31m[!] Something is wrong with the RIGHT ELEVATOR.\033[0m";
                    return false;
                }
                else{
                    cout << "\n\033[1;32m[+] OK. RIGHT ELEVATOR responds.\033[0m";
                    return true;
                }
            }
            else {
                cout << "\n\033[1;31m[!] The BATTERY is OFF. Turn it ON first\033[0m";
                return false;
            }
            //return true;
        }

        else{
            cout << "\n\033[1;31m [!] Operation not permitted : UAV is in the process of reconnaissance\033[0m";
            return false;
        }
    }
    
    bool check_left_elevator(){
        if(!is_in_air){
            if(battery.is_on()){
                if((construction.left_elevator_up() != "up") || (construction.left_elevator_down() != "down")){
                    cout << "\n\033[1;31m[!] Something is wrong with the LEFT ELEVATOR.\033[0m";
                    return false;
                }
                else{
                    cout << "\n\033[1;32m[+] OK. LEFT ELEVATOR responds.\033[0m";
                    return true;
                }
            }
            else {
                cout << "\n\033[1;31m[!] The BATTERY is OFF. Turn it ON first\033[0m";
                return false;
            }
            //return true;
        }

        else{
            cout << "\n\033[1;31m [!] Operation not permitted : UAV is in the process of reconnaissance\033[0m";
            return false;
        }
    }

};

class Pilot{
    private:
        string name, surname;
        int age;
        string qualification; //сертифікат про проходження якогось курсу на пілота бпла
        

    public:

    //constructor

        Pilot(string inputName, string inputSurname, int inputAge, string inputQualification){
            name = inputName;
            surname = inputSurname;
            age = inputAge;
            qualification = inputQualification;
        }

        void battery_on(UAV *uav){
            uav->turnBatteryOn();
        }

        void battery_off(UAV *uav){
            uav->turnBatteryOff();
        }

        void to_catapult(UAV *uav){
            cout << "\n" << name << " " << surname << " is preapring to catapult the UAV...\n";
            uav->takeoff();
        }
};


void Flight_Controller::execute_command(string command, UAV* uav, Servo &servo, ESC &esc, Camera &camera, Telemetry &telemetry){

        if(command == "start_motor"){
            sleep(1);
            cout << "\n\033[1;33m[!] FC has received command, retranslating to ECS\033[0m";
            esc.execute_command(command, uav);
        }

        // else if(command == "takeoff"){
        //     sleep(1);
        //     cout << "\n\033[1;33m[!] FC has received command";
        //     uav->takeoff();
        // }
        else if(command == "land"){
            sleep(1);
            cout << "\n\033[1;33m[!] FC has received command";
            uav->land();
        }
        
        else if((command == "check_right_aileron") || (command == "check_left_aileron") || (command == "check_right_elevator") || (command == "check_left_elevator")){
            sleep(1);
            cout << "\n\033[1;33m[!] FC has received command, retranslating to SERVO\033[0m";
            servo.execute_command(command, uav);
        }
        else if(command == "zoom"){
            sleep(1);
            cout << "\n\033[1;33m[!] FC has received command, retranslating to CAMERA\033[0m"; 
            if(!is_in_air){
                sleep(1);
                cout << "\033[1;31m\n[!] UAV not in the air\033[0m";
                return;
            }
            camera.change_zoom();
        }
        else if(command == "data"){
            sleep(1);
            cout << "\n\033[1;33m[!] FC has received command, retranslating to TELEMETRY\033[0m"; 
            if(!is_in_air){
            sleep(1);
                cout << "\033[1;31m\n[!] UAV not in the air\033[0m";
                return;
            }
            telemetry.send_data();
        }
        else{
            sleep(1);
            cout << "\n[!] Unknown command";
        }
    }

void Servo::execute_command(string command, UAV *uav){
        if(command == "check_right_aileron"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_right_aileron();
            
        }
        else if(command == "check_left_aileron"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_left_aileron();
        }
        else if(command == "check_right_elevator"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_right_elevator();
        }
        else if(command == "check_left_elevator"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_left_elevator();
        }
        else if(command == "turn_left"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_left_elevator();
        }
        else if(command == "turn_right"){
            sleep(1);
            cout << "\n\033[1;33m[!] SERVO has received command\033[0m";
            uav->check_left_elevator();
        }
}

void ESC::execute_command(string command, UAV *uav){
    if(command == "start_motor"){
        sleep(1);
        cout << "\n\033[1;33m[!] ESC has received the command\033[0m";
        uav->start_motor();
        
    }
}

class Ground_Control_Station{
    private:
        UAV* uav;

    public:
    //constructor
        Ground_Control_Station(UAV* u){uav = u;}

        void send_command(string command){
            uav->receive_command(command);
        }
};

int main(){
    
    cout << "\033[1;31m";
    cout << "\n                      -- UAV CONTROL --          ";
    cout << "\n                                                 ";
    cout << "\n                            --*--                ";
    cout << "\n                              +                  ";
    cout << "\n                             +++                 ";
    cout << "\n                .============+++============.    ";
    cout << "\n               *||0000000000000000000000000||*   ";
    cout << "\n             .**=============+++=============**. ";
    cout << "\n                             +++                 ";
    cout << "\n                             +++                 ";
    cout << "\n                             +++                 ";
    cout << "\n                          |__.+.__|              ";
    cout << "\n                              +        \033[0m\n ";

    UAV MINI_SHARK(120, 110, 25, 5);
    Ground_Control_Station gcs(&MINI_SHARK);

    string name, surname, qualification;
    int age;

    cout << "\n\n[!] Register the pilot\n";
    cout << "\n-> Name : "; cin >> name;
    cout << "\n-> Surname : "; cin >> surname;
    cout << "\n-> Age : "; cin >> age;
    if(age < 18){
        cout << "\n\033[1;31m[!] The operator can't be underage.\033[0m" << endl;
        return 1;
    }
    cout << "\n-> Qualification : "; cin >> qualification;
    if((qualification != "БКР_I") && (qualification != "БКР_II") && (qualification != "БКР_III") && (qualification != "БКР_IV")){
        cout << "\n\033[1;31m[!] Wrong input\033[0m" << endl;
        return 1;
    }
    else if((qualification == "БКР_III") || (qualification == "БКР_IV")){
        cout << "\n\033[1;32m[+] OK. The operator was registered\033[0m" << endl;
    }
    else{
        cout << "\n\033[1;31m[!] The operator is not qualified for that type of UAV\033[0m" << endl;
        return 1;
    }
    Pilot pilot(name, surname, age, qualification);

    while(true){
        srand(time(0));

        cout << "\033[34m";
        cout << "\n\n   .-------------------------------------------------------.";
        cout << "\n   |              -- GROUND CONTROL STATION --             |";
        cout << "\n   |*******************************************************|";
        cout << "\n   |                                                       |";
        cout << "\n   |    -- OPTIONS TO INTERACT WITH UAV 'MINI_SHARK' --    |";
        cout << "\n   |                                                       |";
        cout << "\n   | [*] Turn the battery ON  -> \033[1mbattery_on\033[22m;               |";
        cout << "\n   | [*] Turn the battery OFF -> \033[1mbattery_off\033[22m;              |";
        cout << "\n   | [*] Take off the UAV     -> \033[1mtakeoff\033[22m;                  |";
        cout << "\n   | [*] Start the motor      -> \033[1mstart_motor\033[22m;              |";
        cout << "\n   | [*] Land the UAV         -> \033[1mland\033[22m;                     |";
        cout << "\n   |                                                       |";
        cout << "\n   | [*] Check connection:                                 |";
        cout << "\n   |     -> \033[1mcheck_right_aileron\033[22m;                           |";
        cout << "\n   |     -> \033[1mcheck_left_aileron\033[22m;                            |";
        cout << "\n   |     -> \033[1mcheck_right_elevator\033[22m;                          |";
        cout << "\n   |     -> \033[1mcheck_left_elevator\033[22m;                           |";
        cout << "\n   |                                                       |";
        cout << "\n   | [*] Reconnaissance:                                   |";
        cout << "\n   |     [*] Get flight data   -> \033[1mdata\033[22m;                    |";
        cout << "\n   |     [*] Change zoom       -> \033[1mzoom\033[22m;                    |";
        cout << "\n   |                                                       |";
        cout << "\n   .-------------------------------------------------------.\033[0m\n";

        string command;
        cout << "\n-> "; cin >> command;

        if(command == "battery_on"){
            pilot.battery_on(&MINI_SHARK);
            }
        else if(command == "battery_off"){
            pilot.battery_off(&MINI_SHARK);
        }
        else if(command == "takeoff"){
            pilot.to_catapult(&MINI_SHARK);
        }
        else gcs.send_command(command);
    }

}


use std::io::prelude::*;
use std::io::BufReader;
use std::net::{TcpListener, TcpStream, Ipv4Addr, SocketAddrV4};
use std::fs::*;

fn main() {
    let mac_list = read_mac_list("mac.txt");
    let listener = TcpListener::bind("192.168.2.102:8080").expect("Failed while creating socket");
    println!("Started Server at {}", listener.local_addr().unwrap());

    for stream in listener.incoming(){
        handle_connection(stream.unwrap());
    }
}

fn handle_connection(mut client: TcpStream){
    let mut buffer = [0; 512];
    client.read(&mut buffer).unwrap();

    println!("{}", String::from_utf8_lossy(&buffer[..]));
}

//check, if the device is already added
fn check_MAC(mac_addr: String) -> bool{
    
    true
}

fn read_mac_list(path: &str) -> Vec<String>{
    let file_handle = File::open(path).unwrap();
    let reader = BufReader::new(file_handle); 
    let mut mac_list: Vec<String> = Vec::new();

    

    

    vec![String::from("h")]
}




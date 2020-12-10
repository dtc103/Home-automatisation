use std::io;
use std::io::prelude::*;
use std::io::BufReader;
use std::net::{TcpListener, TcpStream, Ipv4Addr, SocketAddrV4};
use std::fs::*;
use std::sync::mpsc;
use std::sync::mpsc::{Receiver, Sender};
use std::thread;
use std::time::Duration;

fn main() {
    let mac_list = read_mac_list("mac.txt").expect("Failed while reading mac list");
    let listener = TcpListener::bind("192.168.178.23:8080").expect("Failed while creating socket");
    println!("Started Server at {}", listener.local_addr().unwrap());

    for stream in listener.incoming(){
        handle_connection(stream.unwrap(), &mac_list);
    }
}

fn handle_connection(mut client: TcpStream, mac_list: &Vec<String>){
    let mut buffer = [0; 512];
    client.read(&mut buffer).unwrap();

    //First thing the device should send is their mac_address, so the server can compare for it
    if check_MAC(String::from(String::from_utf8_lossy(&buffer)), mac_list){
        
    }else{
        //forbidden access
        panic!("YEAH BOOOOY");
    }

    println!("{}", String::from_utf8_lossy(&buffer[..]));
}

//check, if the device is already added
fn check_MAC(mac_addr: String, mac_list: &Vec<String>) -> bool{
    if mac_list.contains(&mac_addr){
        return true
    } else{
        let (tx, rx) = mpsc::channel();
        thread::spawn(move || {
            println!("Do you want to add \n{}?", mac_addr);

            let mut buffer = String::new();
            io::stdin().read_line(&mut buffer).unwrap();

            if buffer.eq(&String::from("y")) || buffer.eq(&String::from("yes")){
                tx.send(buffer).unwrap();
            }
        });

        thread::sleep(Duration::from_secs(5));

        match rx.try_recv(){
            Ok(_) => return true,
            Err(_) => return false,
        }
    }
}

fn read_mac_list(path: &str) -> Result<Vec<String>, io::Error>{
    let file_handle = File::open(path)?;
    let reader = BufReader::new(file_handle); 
    let mut mac_list: Vec<String> = Vec::new();

    for line in reader.lines(){
        mac_list.push(line.unwrap());
    }
    Ok(mac_list)
}




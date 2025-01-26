pub mod camera_controller;

use std::{fs::File, io::{BufRead, BufReader}, process};

#[allow(dead_code)]
#[derive(Debug)]
pub struct Vertex (f32,f32,f32);

pub type Face = Vec<i32>;
pub type Faces = Vec<Face>;

pub fn read_off_file(file: File) -> (Vec<Vertex>, Faces) {
    let reader = BufReader::new(file);
    let mut lines = reader.lines();
    
    let first_line = lines.next().unwrap().unwrap();

    if !first_line.contains("OFF") {
        process::exit(1);
    }

    let second_line = lines.next().unwrap().unwrap();
    let mut spplited_second_line = second_line.split(" ");

    let num_vertices: i32 = spplited_second_line.next().unwrap().parse().unwrap();
    let num_faces: i32 = spplited_second_line.next().unwrap().parse().unwrap();

    let mut vertices: Vec<Vertex> = Vec::new();

    for _ in 0..num_vertices {
        let line = lines.next().unwrap().unwrap();
        let mut spplited_line = line.split(" ");

        let x: f32 = spplited_line.next().unwrap().parse().unwrap();
        let y: f32 = spplited_line.next().unwrap().parse().unwrap();
        let z: f32 = spplited_line.next().unwrap().parse().unwrap();

        vertices.push(Vertex(x,y,z));
    }

    let mut faces: Faces = Vec::new();

    for _ in 0..num_faces {
        let line = lines.next().unwrap().unwrap();
        let mut spplited_line = line.split(" ");

        let face_vertices_count: i32 = spplited_line.next().unwrap().parse().unwrap();
        let mut face_vertices: Face = Vec::new();

        for _ in 0..face_vertices_count {
            let vertex_index: i32 = spplited_line.next().unwrap().parse().unwrap();

            face_vertices.push(vertex_index);
        }

        faces.push(face_vertices);
    }

    (vertices, faces)
}
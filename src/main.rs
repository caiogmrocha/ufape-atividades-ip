use std::{
    env, fs::File, io::{self, BufRead, BufReader}, process
};

#[allow(dead_code)]
struct Vertex (f32,f32,f32);

type Face = Vec<i32>;
type Faces = Vec<Face>;

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let file_path = args[1].as_str();
    let file = File::open(file_path)?;
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

    Ok(())
}

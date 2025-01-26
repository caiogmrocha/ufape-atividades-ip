use bevy::prelude::*;

use std::{
    env,
    fs::File,
    io,
};

use projeto_face_vertice::{
    camera_controller::{CameraController, CameraControllerPlugin},
    read_off_file,
};

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let default = String::from("assets/triangles.off");

    let file_path: &str = args.get(1).unwrap_or_else(|| &default).as_str();

    let file = File::open(file_path)?;

    let (_vertices, _faces) = read_off_file(file);
    
    App::new()
        .add_plugins((DefaultPlugins, CameraControllerPlugin))
        .add_systems(Startup, setup)
        .run();

    Ok(())
}

const CUBE_COLLOR: Color = Color::srgb(255.0, 155.0, 155.0);

fn setup(
    mut commands: Commands,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<StandardMaterial>>,
) {
    commands.spawn((
        Camera3d::default(),
        Transform::from_xyz(0., 1.5, 6.).looking_at(Vec3::ZERO, Vec3::Y),
        CameraController::default(),
    ));

    commands.spawn((
        Mesh3d(meshes.add(Cuboid::new(1.0, 1.0, 1.0))),
        MeshMaterial3d(materials.add(CUBE_COLLOR)),
        Transform::from_xyz(0.0, 0.5, 0.0),
    ));
}
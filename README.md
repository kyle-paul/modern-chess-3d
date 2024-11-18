# 3D Game Chess

## Tasks need done
- [x] Add the spdlog for debugging code
- [x] Abstract the window application
- [ ] Abstract the camera controlling
- [ ] Abstract the environment (lighting, background)
- [ ] Abstract the renderering system (support muliple backend APIs)
- [ ] Abstract the VertexArray, VertexBuffer, IndexBuffer 
- [ ] Abstract the mesh loading
- [ ] Abstract the shading program
- [ ] Abstract the game layers (Game => board => square => piece)
- [ ] Abstract the game rules
- [ ] Add the feature of selecting entity by clicking
- [ ] Add the mode playing with machine
- [ ] Add UI stuffs for users
- [ ] Train Reinforcment Learning with Pytorch
- [ ] Deploy the model with OnnxRuntime


## System design
```
Game
    => Status
    => Rules
    => Chess
        => Board
            => Square
                => Piece
                    => Model
    => Move
```
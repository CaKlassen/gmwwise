// Update the Wwise listener position to the position of the ball
gmwSet2DListenerPosition(x, y, 0, 0);

// Update our own position within the engine
gmwSet2DPosition(id, x, y, 0, 0);

// Check for collisions
var wall = instance_place(x, y, objWall);
if (wall)
{
    // Set the bounce state based on the wall type
    switch(wall.type)
    {
        case WallType.WOOD:
        {
            gmwSetSwitch(global.WWXG_WALL_GROUP, global.WWX_WALL_WOOD, id);
            break;
        }
        
        case WallType.STONE:
        {
            gmwSetSwitch(global.WWXG_WALL_GROUP, global.WWX_WALL_STONE, id);
            break;
        }
    }

    // Play a bounce sound
    gmwPostEvent(global.WWE_BOUNCE, id);
    
    // Bounce
    move_bounce_solid(true);
}


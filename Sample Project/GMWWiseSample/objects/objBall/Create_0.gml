// Constants

MOVE_SPEED = 5;


// Register the object with GMWwise
// This must be done before making engine calls with this object
gmwRegisterObject(id, global.DEFAULT_GROUP, "Ball");


// Starting actions

dir = random(360);
motion_set(dir, MOVE_SPEED);


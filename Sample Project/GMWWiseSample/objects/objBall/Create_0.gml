// Constants

MOVE_SPEED = 5;


// Register the object with GMWwise
// This must be done before making engine calls with this object
gmwRegisterObject(id, "Ball", global.DEFAULT_GROUP);


// Starting actions

dir = random(360);
motion_set(dir, MOVE_SPEED);


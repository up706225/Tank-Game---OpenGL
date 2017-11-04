#ifndef SHAPEARRAY_H_
#define SHAPEARRAY_H_


// array of vertex positions for a generic triangle (drawn with anticlockwise winding (google it) )
//tank array
float myTankArray[] = { 
							-0.6f,	-0.5f,	0.0f, //Bottom left - T1 corner
							0.6f,	-0.5f,	0.0f, //Bottom Right - T1 
							-0.6f,	0.5f,	0.0f, //Top Left - T1
							-0.6f,	0.5f,	0.0f, //Top Left - T2
							0.6f,	-0.5f,	0.0f, //Bottom Right - T2
							0.6f,	0.5f,	0.0f //Top Right - T2 corner
};

// array of corresponding vertex colors, RGBA (note the american spelling of color)
//tank 1 colour array
float myTankColorArray1[] = { 
							1.0,	1.0,	1.0,	1.0,		//Bottom left - T1 corner	
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T1 	
							1.0,	1.0,	1.0,	1.0,		//Top Left - T1  	
							1.0,	1.0,	1.0,	1.0,		//Top Left - T2	
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T2	
							1.0,	1.0,	1.0,	1.0			//Top Right - T2 corner	
};
//tank 1 colour array
float myTankColorArray2[] = { 
							0.0,	0.0,	0.0,	1.0,		//Bottom left - T1 corner	
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T1 	
							0.0,	0.0,	0.0,	1.0,		//Top Left - T1  	
							0.0,	0.0,	0.0,	1.0,		//Top Left - T2	
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T2	
							0.0,	0.0,	0.0,	1.0			//Top Right - T2 corner	
};
//turret array
float myTurretArray[] = { 
							-0.3f,	-0.3f,	0.0f, //Bottom left - T1 corner
							0.3f,	-0.3f,	0.0f, //Bottom Right - T1 
							-0.3f,	0.3f,	0.0f, //Top Left - T1
							-0.3f,	0.3f,	0.0f, //Top Left - T2
							0.3f,	-0.3f,	0.0f, //Bottom Right - T2
							0.3f,	0.3f,	0.0f, //Top Right - T2 corner
							0.3f,	-0.1f,	0.0f, //Bottom left - T3 corner
							0.7f,	-0.1f,	0.0f, //Bottom Right - T3 
							0.3f,	0.1f,	0.0f, //Top Left - T3
							0.3f,	0.1f,	0.0f, //Top Left - T4
							0.7f,	-0.1f,	0.0f, //Bottom Right - T4
							0.7f,	0.1f,	0.0f //Top Right - T4 corner
};

//tank 1 turret colour array
float myTurretColorArray1[] = { 
							0.0,	0.0,	0.0,	1.0, 		//Bottom left - T1 corner
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T1 
							0.0,	0.0,	0.0,	1.0,	  	//Top Left - T1
							0.0,	0.0,	0.0,	1.0,		//Top Left - T2
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T2
							0.0,	0.0,	0.0,	1.0,		//Top Right - T2 corner
							0.0,	0.0,	0.0,	1.0,		//Bottom left - T3 corner
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T3 
							0.0,	0.0,	0.0,	1.0,	  	//Top Left - T3
							0.0,	0.0,	0.0,	1.0,		//Top Left - T4
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T4
							0.0,	0.0,	0.0,	1.0			//Top Right - T4 corner
};
//tank 2 turret colour array
float myTurretColorArray2[] = { 
							1.0,	1.0,	1.0,	1.0, 		//Bottom left - T1 corner
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T1 
							1.0,	1.0,	1.0,	1.0,	  	//Top Left - T1
							1.0,	1.0,	1.0,	1.0,		//Top Left - T2
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T2
							1.0,	1.0,	1.0,	1.0,		//Top Right - T2 corner
							1.0,	1.0,	1.0,	1.0,		//Bottom left - T3 corner
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T3 
							1.0,	1.0,	1.0,	1.0,	  	//Top Left - T3
							1.0,	1.0,	1.0,	1.0,		//Top Left - T4
							1.0,	1.0,	1.0,	1.0,		//Bottom Right - T4
							1.0,	1.0,	1.0,	1.0			//Top Right - T4 corner
};
//bullet array
float myBulletArray[] = { 
							-0.1f,	-0.08f,	0.0f, //Bottom left - T1 corner
							0.1f,	-0.08f,	0.0f, //Bottom Right - T1 
							-0.1f,	0.08f,	0.0f, //Top Left - T1
							-0.1f,	0.08f,	0.0f, //Top Left - T2
							0.1f,	-0.08f,	0.0f, //Bottom Right - T2
							0.1f,	0.08f,	0.0f //Top Right - T2 corner
};
//bullet colour array
float myBulletColorArray[] = { 
							0.0,	0.0,	0.0,	1.0, 		//Bottom left - T1 corner
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T1 
							0.0,	0.0,	0.0,	1.0,	  	//Top Left - T1
							0.0,	0.0,	0.0,	1.0,		//Top Left - T2
							0.0,	0.0,	0.0,	1.0,		//Bottom Right - T2
							0.0,	0.0,	0.0,	1.0,		//Top Right - T2 corner

};
//sheild pickup array
float sheildPickupArray[] = { 
							-0.3f,	-0.3f,	0.0f,		//Bottom left - T1 corner
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T1 
							-0.3f,	0.3f,	0.0f,		//Top Left - T1
							-0.3f,	0.3f,	0.0f,		//Top Left - T2
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T2
							0.3f,	0.3f,	0.0f,		//Top Right - T2 corner
							-0.225f,-0.225f,0.0f,		//Bottom left - T3 corner
							0.225f,-0.225f, 0.0f,		//Bottom Right - T3 
							-0.225f,0.225f,	0.0f,		//Top Left - T3
							-0.225f,0.225f,	0.0f,		//Top Left - T4
							0.225f,	-0.225f,0.0f,		//Bottom Right - T4
							0.225f,	0.225f,	0.0f			//Top Right - T4 corner
};
//sheild pickup colour array
float sheildPickupColourArray[] = { 
							0.1f,	0.1f,	0.1f,	1.0f, 		//Bottom left - T1 corner
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T1 
							0.1f,	0.1f,	0.1f,	1.0f,	  	//Top Left - T1
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Left - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Right - T2 corner
							0.0f,	1.0f,	0.0f,	1.0f,		//Bottom left - T3 corner
							0.0f,	1.0f,	0.0f,	1.0f,		//Bottom Right - T3 
							0.0f,	1.0f,	0.0f,	1.0f,	  	//Top Left - T3
							0.0f,	1.0f,	0.0f,	1.0f,		//Top Left - T4
							0.0f,	1.0f,	0.0f,	1.0f,		//Bottom Right - T4
							0.0f,	1.0f,	0.0f,	1.0f			//Top Right - T4 corner
};
//specialshot pickup array
float specialPickupArray[] = { 
							-0.3f,	-0.3f,	0.0f,		//Bottom left - T1 corner
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T1 
							-0.3f,	0.3f,	0.0f,		//Top Left - T1
							-0.3f,	0.3f,	0.0f,		//Top Left - T2
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T2
							0.3f,	0.3f,	0.0f,		//Top Right - T2 corner
							-0.225f,-0.225f,0.0f,		//Bottom left - T3 corner
							0.225f,-0.225f, 0.0f,		//Bottom Right - T3 
							-0.225f,0.225f,	0.0f,		//Top Left - T3
							-0.225f,0.225f,	0.0f,		//Top Left - T4
							0.225f,	-0.225f,0.0f,		//Bottom Right - T4
							0.225f,	0.225f,	0.0f			//Top Right - T4 corner
};
//specialshot pickup colour array
float specialPickupColourArray[] = { 
							0.1f,	0.1f,	0.1f,	1.0f, 		//Bottom left - T1 corner
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T1 
							0.1f,	0.1f,	0.1f,	1.0f,	  	//Top Left - T1
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Left - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Right - T2 corner
							1.0f,	0.0f,	0.0f,	1.0f,		//Bottom left - T3 corner
							1.0f,	0.0f,	0.0f,	1.0f,		//Bottom Right - T3 
							1.0f,	0.0f,	0.0f,	1.0f,	  	//Top Left - T3
							1.0f,	0.0f,	0.0f,	1.0f,		//Top Left - T4
							1.0f,	0.0f,	0.0f,	1.0f,		//Bottom Right - T4
							1.0f,	0.0f,	0.0f,	1.0f			//Top Right - T4 corner
};
//grenade pickup array
float grenadePickupArray[] = { 
							-0.3f,	-0.3f,	0.0f,		//Bottom left - T1 corner
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T1 
							-0.3f,	0.3f,	0.0f,		//Top Left - T1
							-0.3f,	0.3f,	0.0f,		//Top Left - T2
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T2
							0.3f,	0.3f,	0.0f,		//Top Right - T2 corner
							-0.225f,-0.225f,0.0f,		//Bottom left - T3 corner
							0.225f,-0.225f, 0.0f,		//Bottom Right - T3 
							-0.225f,0.225f,	0.0f,		//Top Left - T3
							-0.225f,0.225f,	0.0f,		//Top Left - T4
							0.225f,	-0.225f,0.0f,		//Bottom Right - T4
							0.225f,	0.225f,	0.0f			//Top Right - T4 corner
};
//grenade pickup colour array
float grenadePickupColourArray[] = { 
							0.1f,	0.1f,	0.1f,	1.0f, 		//Bottom left - T1 corner
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T1 
							0.1f,	0.1f,	0.1f,	1.0f,	  	//Top Left - T1
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Left - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Right - T2 corner
							1.0f,	0.5f,	0.0f,	1.0f,		//Bottom left - T3 corner
							1.0f,	0.5f,	0.0f,	1.0f,		//Bottom Right - T3 
							1.0f,	0.5f,	0.0f,	1.0f,	  	//Top Left - T3
							1.0f,	0.5f,	0.0f,	1.0f,		//Top Left - T4
							1.0f,	0.5f,	0.0f,	1.0f,		//Bottom Right - T4
							1.0f,	0.5f,	0.0f,	1.0f			//Top Right - T4 corner

};
//speedboost pickup array
float speedPickupArray[] = { 
							-0.3f,	-0.3f,	0.0f,		//Bottom left - T1 corner
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T1 
							-0.3f,	0.3f,	0.0f,		//Top Left - T1
							-0.3f,	0.3f,	0.0f,		//Top Left - T2
							0.3f,	-0.3f,	0.0f,		//Bottom Right - T2
							0.3f,	0.3f,	0.0f,		//Top Right - T2 corner
							-0.225f,-0.225f,0.0f,		//Bottom left - T3 corner
							0.225f,-0.225f, 0.0f,		//Bottom Right - T3 
							-0.225f,0.225f,	0.0f,		//Top Left - T3
							-0.225f,0.225f,	0.0f,		//Top Left - T4
							0.225f,	-0.225f,0.0f,		//Bottom Right - T4
							0.225f,	0.225f,	0.0f			//Top Right - T4 corner
};
//speedboost pickup colour array
float speedPickupColourArray[] = { 
							0.1f,	0.1f,	0.1f,	1.0f, 		//Bottom left - T1 corner
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T1 
							0.1f,	0.1f,	0.1f,	1.0f,	  	//Top Left - T1
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Left - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Bottom Right - T2
							0.1f,	0.1f,	0.1f,	1.0f,		//Top Right - T2 corner
							0.0f,	0.0f,	1.0f,	1.0f,		//Bottom left - T3 corner
							0.0f,	0.0f,	1.0f,	1.0f,		//Bottom Right - T3 
							0.0f,	0.0f,	1.0f,	1.0f,	  	//Top Left - T3
							0.0f,	0.0f,	1.0f,	1.0f,		//Top Left - T4
							0.0f,	0.0f,	1.0f,	1.0f,		//Bottom Right - T4
							0.0f,	0.0f,	1.0f,	1.0f			//Top Right - T4 corner
};
#endif /* SHAPEARRAY_H_ */
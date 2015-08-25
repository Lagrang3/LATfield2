#ifndef LATFIELD2_PARTICLE_DEF_HPP
#define LATFIELD2_PARTICLE_DEF_HPP

/*type table
 
 datatype      memType         fileType
 int            H5T_NATIVE_INT   INT_TYPE_FILE
 long           H5T_NATIVE_LONG  INT_TYPE_FILE
 float          H5T_NATIVE_FLOAT  FLOAT_TYPE_FILE
 double         H5T_NATIVE_DOUBLE  DOUBLE_TYPE_FILE
 bool           H5T_NATIVE_HBOOL  BOOL_TYPE_FILE
 */



// part_simple definition
struct part_simple{
  
  long ID;
  LATfield2::Real pos[3];
  LATfield2::Real vel[3];
};
ostream& operator<<(ostream& os, const part_simple& p)
{
    os << "ID: "<<p.ID<<" , Pos: ("<< p.pos[0]<<","<< p.pos[1]<<","<< p.pos[2]<<") , Vel: (" << p.vel[0]<<","<< p.vel[1]<<","<< p.vel[2]<<")"; 
    return os;
}

struct part_simple_info{
    double  mass;
    int relativistic;
    int type_name_size;
    char  type_name[64];
    
};


template<typename pInfo>
void set_parts_typename(pInfo *info, string type_name){
    
    info->type_name_size = type_name.size();
    //info->type_name = new char[info->type_name_size];
    strcpy(info->type_name,type_name.c_str());
    
}


#ifdef HDF5
struct part_simple_dataType{
  hid_t part_memType;
  hid_t part_fileType;
  hid_t part_info_memType;
  hid_t part_info_fileType;

  part_simple_dataType(){

    hid_t strtype = H5Tcopy (H5T_C_S1);
    H5Tset_size (strtype, 64);
    
    
    part_memType = H5Tcreate(H5T_COMPOUND, sizeof (part_simple)); 
    H5Tinsert(part_memType, "ID", HOFFSET (part_simple, ID), H5T_NATIVE_LONG);
    H5Tinsert(part_memType, "positionX", HOFFSET (part_simple, pos[0]), REAL_TYPE);
    H5Tinsert(part_memType, "positionY", HOFFSET (part_simple, pos[1]), REAL_TYPE);
    H5Tinsert(part_memType, "positionZ", HOFFSET (part_simple, pos[2]), REAL_TYPE);
    H5Tinsert(part_memType, "velocityX", HOFFSET (part_simple, vel[0]), REAL_TYPE);
    H5Tinsert(part_memType, "velocityY", HOFFSET (part_simple, vel[1]), REAL_TYPE);
    H5Tinsert(part_memType, "velocityZ", HOFFSET (part_simple, vel[2]), REAL_TYPE);
    


    part_info_memType = H5Tcreate(H5T_COMPOUND, sizeof (part_simple_info));
    H5Tinsert(part_info_memType, "mass", HOFFSET (part_simple_info, mass), H5T_NATIVE_DOUBLE);
    H5Tinsert(part_info_memType, "relativistic", HOFFSET (part_simple_info, relativistic), INT_TYPE_FILE);
    H5Tinsert(part_info_memType, "type_name_size", HOFFSET (part_simple_info, type_name_size),INT_TYPE_FILE );
    H5Tinsert(part_info_memType, "type_name", HOFFSET (part_simple_info, type_name), strtype);

    
    part_fileType = H5Tcreate (H5T_COMPOUND, sizeof(long) + 6 * sizeof(Real) );
    H5Tinsert(part_fileType, "ID"       ,0  ,H5T_STD_I64BE);
    H5Tinsert(part_fileType, "positionX",sizeof(long)                    ,REAL_TYPE_FILE);
    H5Tinsert(part_fileType, "positionY",sizeof(long) + 1 * sizeof(Real) ,REAL_TYPE_FILE);
    H5Tinsert(part_fileType, "positionZ",sizeof(long) + 2 * sizeof(Real) ,REAL_TYPE_FILE);
    H5Tinsert(part_fileType, "velocityX",sizeof(long) + 3 * sizeof(Real) ,REAL_TYPE_FILE);
    H5Tinsert(part_fileType, "velocityY",sizeof(long) + 4 * sizeof(Real) ,REAL_TYPE_FILE);
    H5Tinsert(part_fileType, "velocityZ",sizeof(long) + 5 * sizeof(Real) ,REAL_TYPE_FILE);
      
    part_info_fileType = H5Tcreate(H5T_COMPOUND, sizeof(double) +(2*sizeof(int))+ 64);
    H5Tinsert(part_info_fileType, "mass", 0 ,DOUBLE_TYPE_FILE );
    H5Tinsert(part_info_fileType, "relativistic",sizeof(double), INT_TYPE_FILE);
    H5Tinsert(part_info_fileType, "type_name_size", sizeof(double)+sizeof(int),INT_TYPE_FILE );
    H5Tinsert(part_info_fileType, "type_name",sizeof(double)+(2*sizeof(int)), strtype);

    H5Tclose (strtype);
  }
    
};
#endif









#endif

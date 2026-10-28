typedef unsigned int u32;
struct CoordinateCurve {
    int from_x,from_y,to_x,to_y,sign_x,sign_y;
    u32 delta_x,delta_y;
    int error,half_delta_y;
    u32 full_delta_y;
};
typedef char CoordinateCurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
void CoreFrontier_000075CC(struct CoordinateCurve *curve,int from_x,int from_y,int to_x,int to_y)
{
    u32 dy;
    curve->from_x=from_x;
    curve->from_y=from_y;
    curve->to_x=to_x;
    curve->to_y=to_y;
    curve->delta_x=(u32)to_x-(u32)from_x;
    if((int)curve->delta_x<0) {
        curve->delta_x=0u-curve->delta_x;
        curve->sign_x=-1;
    } else curve->sign_x=1;
    curve->delta_y=(u32)to_y-(u32)from_y;
    if((int)curve->delta_y<0) {
        curve->delta_y=0u-curve->delta_y;
        curve->sign_y=-1;
    } else curve->sign_y=1;
    dy=curve->delta_y;
    curve->half_delta_y=(int)dy>>1;
    curve->error=0;
    curve->full_delta_y=dy;
    if(dy==0)curve->from_x=to_x;
}

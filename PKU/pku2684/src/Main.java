import java.awt.geom.Point2D;
import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Main {
    
    private static boolean debug = true;

    public static class Polygon{
        ArrayList<Point2D> list;
        public int N;

        public void setPoint(double x, double y){
            Point2D.Double p = new Point2D.Double(x, y);
            list.add(p);
        }
        
        public void movePoint(double x, double y){
             for(Point2D p : list){
                double nx = p.getX() + x;
                double ny = p.getY() + y;
                p.setLocation(nx, ny);
            }           
        }
        public void rotate90(){
            for(Point2D p : list){
                double nx = -p.getY();
                double ny = p.getX();
                p.setLocation(nx, ny);
            }
        }
        public boolean checkCorrespond(Polygon polygon){
            
            int find = 0;
            for(Point2D p1 : list){
                for(Point2D p2: polygon.list){
                    if(p1.distance(p2) == 0){
                        find ++;
                    }
                }
            }
            if(find == N){
                return true;
            }
            return false;
        }
        public Polygon(int n) {
            list = new ArrayList<Point2D>(n);
            N = n;
        }
    };
    
    private static void rotate90(Point2D p){
        double nx = p.getY();
        double ny = p.getX();
        p.setLocation(nx, ny);
    }
    
    
    public static void main(String args[]){
        Scanner scan = null;
        
        if(!debug){
            scan = new Scanner(System.in);
        }
        else{
            File file = new File("input.txt");
            try {
                scan = new Scanner(file);
            } catch (FileNotFoundException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        int datanum = datanum = scan.nextInt();
        
        while(datanum != 0){

            int pointnum = scan.nextInt();
            Polygon template = new Polygon(pointnum);
            for(int j = 0; j < pointnum; j++){
                double x = scan.nextDouble();
                double y = scan.nextDouble();
                template.setPoint(x, y);
            }
            if(template.list.get(0).distance(0, 0) != 0){
                double vx = template.list.get(0).getX();
                double vy = template.list.get(0).getY();
                template.movePoint(-vx, -vy);
            }
            
            for(int i = 0; i < datanum; i++){
                int pnum = scan.nextInt();
                Polygon polygon = new Polygon(pointnum);
                for(int j = 0; j < pointnum; j++){
                    double x = scan.nextDouble();
                    double y = scan.nextDouble();
                    polygon.setPoint(x, y);
                }
                
                for(Point2D point:polygon.list){
                    if(point.distance(0, 0) != 0){
                        polygon.movePoint(-point.getX(), -point.getY());
                    }

                    for(int k =0; k < 4; k++){                            
                        if(polygon.checkCorrespond(template)){
                            System.out.println(i+1);
                            break;
                        }
                        polygon.rotate90();
                    }
                    

                }

            }
            System.out.println("+++++");
            datanum = scan.nextInt();
        }
        
    }
        
       
}

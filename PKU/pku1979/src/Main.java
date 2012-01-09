import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author yasuhiro-i
 */
public class Main {
    
    private static boolean debug = true;
    private static final int maxw = 25;
    private static final int maxh = 25;
    private static int[][] map = new int[maxh][maxw];
    private static HashMap<Character, Integer> hmp = new HashMap<Character, Integer>();
    private static final int[][] seq = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    private static int counter = 0;
    
    enum mapval{
        init(0),
        black(1),
        red(2),
        start(3),
        reached(4);
       private final int num;
       private mapval(int i){this.num = i;}
       public int num(){return num;}
    }
    
    private static void setHash(){
        hmp.put('.', mapval.black.num());
        hmp.put('#', mapval.red.num());
        hmp.put('@', mapval.start.num());
        hmp.put(' ', mapval.init.num());
    }
    
    public static void initmap(){
        for(int iy = 0; iy < maxh; iy++){
            for(int ix = 0; ix < maxw; ix++){
                map[iy][ix] = mapval.red.num();
            }
        }
    }
    
    private static boolean walk(int x, int y){
       
        if(map[y][x] == mapval.black.num){
            map[y][x] = mapval.reached.num;
            counter++;
        }else{
            
        }
        
        for(int i =0; i < 4; i++){
            int vx = seq[i][0];
            int vy = seq[i][1];
            int nx = x+vx;
            int ny = y+vy;
            
            if(map[ny][nx] == mapval.black.num){
                walk(nx, ny);
                
            }else{
                continue;
            }
        
        }
        
        return true;
    }
    
    public static void main(String args[]){
        Scanner scan = null;
        
        if(!debug){
            scan = new Scanner(System.in);
        }
        else{
            File file = new File("src\\input.txt");
            try {
                scan = new Scanner(file);
            } catch (FileNotFoundException ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        setHash();
        
        while(true){
            initmap();
            Integer w, h;

            w = scan.nextInt();
            h = scan.nextInt();
            
            if(w == 0 && h == 0){
                break;
            }
            
            int startx = 0, starty = 0;
            for(int iy = 1; iy <= h; iy++){
                String line = scan.next();
                for(int ix = 0; ix < line.length(); ix++){
                    Character ch = line.charAt(ix);
                    int val = hmp.get(ch);
                    map[iy][ix+1] = val;
                    if(val == mapval.start.num){
                        startx = ix+1;
                        starty = iy;
                    }
                }
            }

            counter = 0;
            walk(startx, starty);
            System.out.println(counter+1);
        }
        
        
    }
}

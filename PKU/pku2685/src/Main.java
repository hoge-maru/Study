import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
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
    
    private static boolean debug = false;
    private static Integer num = 0;
    
    public static String convertMCXIFromInt(Integer val) throws Exception{
        int basic = val;
        
        int m_pre = val/1000;
        val -=  m_pre*1000;
        
        int c_pre = val / 100;
        val -= c_pre*100;
        
        int x_pre = val / 10;
        val -= x_pre*10;
        
        int i_pre = val;
        
        //check
        if(m_pre*1000+c_pre*100+x_pre*10+i_pre != basic){
            throw new Exception("invalid calc");
        }
       
        
        String rtn = "";
        class inner{
            public int pre;
            public char c;

            public inner(int pre, char c) {
                this.pre = pre;
                this.c = c;
            }
            
        };
        final inner objm = new inner(m_pre, 'm');
        final inner objc = new inner(c_pre, 'c');
        final inner objx = new inner(x_pre, 'x');
        final inner obji = new inner(i_pre, 'i');
        List<inner> list = new ArrayList<inner>(){{
            add(objm);add(objc);add(objx);add(obji);
        }};
        for(inner obj:list){
            if(obj.pre > 1){
                String ptn = String.valueOf(obj.pre).concat(String.valueOf(obj.c));
                rtn = rtn.concat(ptn);
            }else if(obj.pre == 1){
                String ptn = String.valueOf(obj.c);
                rtn = rtn.concat(ptn);                
            }
        }
     
        return rtn;
    }
    
    public static Integer convertIntFromMCXI(String str){
        
        int rtn =0;
        int prefix = 1;
        for(int i = 0; i < str.length(); i++){
            char c = str.charAt(i);
            if(c == 'm'){
                int tmp = prefix * 1000;
                rtn += tmp;
                prefix = 1;
            }else if(c == 'c'){
                int tmp = prefix * 100;
                rtn += tmp;
                prefix = 1;
            }else if(c == 'x'){
                int tmp = prefix * 10;
                rtn += tmp;
                prefix = 1;
            }else if(c == 'i'){
                int tmp = prefix * 1;
                rtn += tmp;
                prefix = 1;
            }else{
                prefix = Integer.parseInt(""+c);
            }
        }
        
        return rtn;
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
        num = scan.nextInt();

        while(num-- > 0){
        
            String str1 = scan.next();
            String str2 = scan.next();

            Integer val1 = convertIntFromMCXI(str1);
            Integer val2 = convertIntFromMCXI(str2);

            Integer sum = val1+val2;
            String summcxi = null;
            try {
                summcxi = convertMCXIFromInt(sum);
            } catch (Exception ex) {
                Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
            }

            System.out.println(summcxi);
        }
        
    }
}

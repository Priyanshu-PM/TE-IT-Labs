import java.util.*;
public class BellmanFord 
{
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of vertices");
        int v=sc.nextInt();

        int shortest[] = new int[v];

        System.out.println("Enter number of edges");
        int e=sc.nextInt();

        System.out.println("Enter edge one by one in following format: starting vertex , ending vertex , weight");

        int graph[][] = new int[e][3];
        for(int i=0;i<e;i++)
        {
            graph[i][0]=sc.nextInt(); // Starting Index
            graph[i][1]=sc.nextInt(); //Ending index
            graph[i][2]=sc.nextInt(); // Weight
        }

        ArrayList<ArrayList<Integer>> ar1 = new ArrayList<>();
        ArrayList<Integer> temp ;
        for(int i=0;i<v;i++)
        {
            temp = new ArrayList<>();
            temp.add(0);
            ar1.add(temp);
        }

        ArrayList<Integer> st;
        ArrayList<Integer> end;
        Arrays.fill(shortest,Integer.MAX_VALUE/10);
        shortest[0]=0;
        for(int i=1;i<v;i++)
        {
            for(int j=0;j<e;j++)
            {
                if((shortest[graph[j][0]]+graph[j][2])<shortest[graph[j][1]])
                {
                    shortest[graph[j][1]]=shortest[graph[j][0]] + graph[j][2]; 
                    
                    st=ar1.get(graph[j][0]);
                    end=new ArrayList<>(st);
                    end.add(graph[j][1]);
                    ar1.set(graph[j][1],end);
                    
                }
            }
        }

        System.out.println("Shortest paths and their distances respectively are");

        for(int i=0;i<shortest.length;i++)
        {
            System.out.println("Vertice:- " +i+" Distance:- "+shortest[i]+"\t\tPath: "+ar1.get(i));
        }



    }    
}
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashMap;

public class InfoLogin {
	private HashMap<String,Usuario> logs = new HashMap<String,Usuario>();
	
	
	
	@SuppressWarnings("unchecked")//podemos fazer isso pois sempre será inserido a mesma coisa em logs.ser
	public InfoLogin(){
		try { 
			FileInputStream file = new FileInputStream("logins.ser");
			ObjectInputStream in = new ObjectInputStream(file);
			this.logs = (HashMap<String, Usuario>) in.readObject();
			System.out.printf("Li o hashMap! \n %s\n",logs.toString());
			in.close();
			file.close();
		} catch (FileNotFoundException e) {
			this.writeFile();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public int add(Usuario usuario, String senha) {
		if(logs.containsKey(senha)) return -1;
		logs.put(senha, usuario);
		writeFile();
		return 0;
	}
	
	
	protected HashMap<String,Usuario> getLogs(){
		//System.out.print(logs.toString());
		return logs;
	}
	
	public int writeFile(){// escreve em um arquivo a serialização dos conteúdos de uma comunidade
		try {
			FileOutputStream file = new FileOutputStream("logins.ser");
			ObjectOutputStream out = new ObjectOutputStream(file);
			out.writeObject(this.logs);
			System.out.printf("Escrevi o HashMap dos Logins!\n%s\n", this.logs);
			out.close();
			file.close();
		} catch (IOException e) {
			System.out.println("Arquivo não existente");
			e.printStackTrace();
		}
		return 0;
	}
	
}	

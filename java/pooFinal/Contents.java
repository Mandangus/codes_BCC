import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashMap;

public class Contents {
	
	private HashMap<String, Tema> content = new HashMap<String, Tema>();
	
	public int add(String titulo, Tema t) {// adiciona um valor nao ja adicionado ao HashMap de temas
		if(content.containsKey(titulo)) return -1;
		content.put(titulo, t);
		return 0;
	} 
	
	protected HashMap<String , Tema> getContents(){
		return content;
	}
	
	@SuppressWarnings("unchecked") // podemos suprimir esse warning pois só vamos inserir o mesmo tipo HashMap<String, Tema>
	public int getHash(String filenameSer){// le do arquivo serial o HashMap de temas mas caso não exista o arquivo retorna -1 de erro
		try {
			FileInputStream file = new FileInputStream(filenameSer);
			ObjectInputStream in = new ObjectInputStream(file);
			content = (HashMap<String, Tema>)in.readObject();
			file.close();
		} catch (IOException | ClassNotFoundException e) {
			System.out.println("Arquivo não existente");
			e.printStackTrace();
			return -1;
		}
		return 0;
	}
	
	
	public void updateFile(String filenameSer) {// escreve para o arquivo serial o HashMap atualizado com os temas
		try {
			FileOutputStream file = new FileOutputStream(filenameSer);
			ObjectOutputStream out = new ObjectOutputStream(file);
			out.writeObject(getContents());
			out.close();
			file.close();
		} catch (FileNotFoundException e) {
			System.out.println("Arquivo da comunidade não existente");
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
	
}

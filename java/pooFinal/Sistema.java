import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.HashMap;

public class Sistema {
	// HashMap com nomes de arquivos e id's de comunidades
	protected HashMap<String,Integer> sis = new HashMap<String,Integer>();
	
	
	public Sistema() {
		readFile("Sistema.ser");
	}
	
	
	public int add(Comunidade c) {
		if(sis.containsKey(c.titulo)) return -1;// se ja existe retorna
		sis.put(c.titulo, c.id);
		try {
			c.writeFile();//	caso contrario escreva o arquivo .ser e coloque no HashMap
		} catch (IOException e) {
			e.printStackTrace();
		}
		return 0;
	}
	
	
	private void writeFile(String filenameSer){
		try {// tentamos escrever para o arquivo serial
			FileOutputStream file = new FileOutputStream(filenameSer);
			ObjectOutputStream out = new ObjectOutputStream(file);
			out.writeObject(sis); 
			System.out.printf("Escrevi o HashMap do sis!\n%s\n", sis.toString());
			out.close();
			file.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	@SuppressWarnings("unchecked")
	private void readFile(String filenameSer){
		try {//tentamos ler um arquivo serial padrao Sistema.ser, caso não exista escrevemos
			FileInputStream file = new FileInputStream(filenameSer);
			ObjectInputStream in = new ObjectInputStream(file);
			sis = (HashMap<String, Integer>)in.readObject();
			file.close();
		} catch (ClassNotFoundException e) {
			System.out.println("Classe não existente");
			e.printStackTrace();
			return;
		} catch (FileNotFoundException e) {
			System.out.println("Arquivo do Sistema não existente");
			writeFile(filenameSer);
			return;
		} catch (IOException e) {
			System.out.println("Problema IO");
			e.printStackTrace();
			return;
		}
		return;
	}
	
	
	public HashMap<String,Integer> getSis(String filenameSis){
		readFile("Sistema.ser");
		return this.sis;
	}
	
	public void close() {
		writeFile("Sistema.ser");
		return;
	}
	
}

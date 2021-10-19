import java.io.*;

public class Comunidade {

	private Contents contents = new Contents();// Hash map dos conteudos do arquivo
	String titulo;
	Integer id;
	private String filenameSer;// nome do aqruivo serializado do HashMap<Tema,String>.
	
	
	
	public Comunidade(String titulo, int id) {
		this.titulo = titulo;
		this.id = id;
		filenameSer = titulo + ".ser";
	}
	
	@Override
	public String toString() {
		String s = "Titulo: " + titulo  + "\n" + "Nome do arquivo: " + filenameSer;
		return s;
	}
	
	
	public int writeFile() throws IOException {// escreve em um arquivo a serialização dos conteúdos de uma comunidade
		try {
			FileOutputStream file = new FileOutputStream(filenameSer);
			ObjectOutputStream out = new ObjectOutputStream(file);
			out.writeObject(contents.getContents());
			out.close();
			file.close();
		} catch (FileNotFoundException e) {
			System.out.println("Arquivo da comunidade não existente");
			e.printStackTrace();
		}
		return 0;
	}
	public int readFile() throws IOException, ClassNotFoundException {// le um arquivo e coleta a hash contendo os temas e titulos da comunidade
		int status = contents.getHash(filenameSer);
		return status;
	}
	
}
 
import java.io.*;
import java.util.ArrayList;

public class Main {

	public static void main(String[] args) throws IOException, ClassNotFoundException {
		InfoLogin listLogin = new InfoLogin();// criamos um objeto para lidar com os logins
		Sistema sis = new Sistema(); // criamos um objeto para lidar com as comunidades
		ArrayList<String> array = new ArrayList<String>();
		array.add(" ");
		array.add("Adicionar nova comunidade");
		sis.sis.forEach((k,v)->array.add(k));
		String[] titulos = array.toArray(new String[0]);// criamos a entrada inicial de titulos de comunidades
		@SuppressWarnings("unused")
		LoginPage l = new LoginPage(listLogin.getLogs(),titulos);// iniciamos a pagina de login
		sis.close();
	}

}

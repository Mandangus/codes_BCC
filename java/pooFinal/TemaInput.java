import javax.swing.*;

import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TemaInput implements ActionListener{
	
	JFrame frame = new JFrame();
	JLabel bemvindo = new JLabel();
	
	
	JLabel temaIDLabel = new JLabel("Titulo: ");
	JTextField temaIDField = new JTextField();
	
	JLabel temaInterLabel = new JLabel("Texto informativo: ");
	JTextArea temaInterField = new JTextArea();
	
	JLabel temaDescLabel = new JLabel("Links:");
	JTextArea temaDescField = new JTextArea("separados por virgula");	
	
	JButton botao = new JButton();
	JButton adicionar = new JButton();
	
	String comName = new String();
	
	JLabel warning = new JLabel("Todos os campos com * devem ser preenchidos!");
	
	public TemaInput(String comName){
		
		this.comName = comName;
		

		bemvindo.setBounds(10,0,200,35);
		bemvindo.setFont(new Font(null,Font.BOLD,20));
		bemvindo.setText("Adicionar um tema!");
		
		temaIDLabel.setBounds(10,35,200,35);
		temaIDLabel.setFont(new Font(null,Font.ITALIC,15));
		
		temaIDField.setBounds(75,40,200,25);
		
		temaInterLabel.setBounds(10,105,200,25);
		temaInterLabel.setFont(new Font(null,Font.ITALIC,15));
		
		temaInterField.setBounds(150,110,200,150);
		temaInterField.setLineWrap(true);
		temaInterField.setWrapStyleWord(true);
		temaInterField.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		
		temaDescLabel.setBounds(10,265,200,25);
		temaDescLabel.setFont(new Font(null,Font.ITALIC,15));
		
		temaDescField.setBounds(150,270,200,150);
		temaDescField.setLineWrap(true);
		temaDescField.setWrapStyleWord(true);
		temaDescField.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		
		
		botao.setBounds(100,500,200,30);
		botao.setText("Confirmar");
		botao.addActionListener(this);
		
		warning.setBounds(10,660,300,10);
		warning.setFont(new Font(null,Font.BOLD,10));
		warning.setForeground(Color.RED);
		warning.setVisible(false);
		
		frame.add(bemvindo);
		frame.add(temaIDLabel);
		frame.add(temaIDField);
		frame.add(temaInterLabel);
		frame.add(temaInterField);
		frame.add(temaDescLabel);
		frame.add(temaDescField);
		frame.add(botao);
		frame.add(warning);
		
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setSize(420, 600);
		frame.setLayout(null);
		frame.setVisible(true);
	}
	
	 
	
	@Override
	public void actionPerformed(ActionEvent e) {// coletamos os dados de cada campo e atribuimos para o tema
		String titulo = temaIDField.getText();
		String text = temaInterField.getText();
		String[] links = temaDescField.getText().split(", ");
		Tema t = new Tema(titulo,links,text);
		Contents c = new Contents();
		c.getHash(comName + ".ser");
		c.getContents().put(titulo, t);
		c.updateFile(comName + ".ser");
		frame.dispose();
	}
	
}

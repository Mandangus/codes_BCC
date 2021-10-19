import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class WelcomePage implements ActionListener{

	JFrame frame = new JFrame();
	JLabel welcomeLabel = new JLabel();
	
	JLabel searchLabel = new JLabel("Pesquisar por temas:");
	JTextField searchField = new JTextField();
	
	JTextArea prompt = new JTextArea();
	
	JLabel userAge = new JLabel();
	JLabel userInter = new JLabel();
	JLabel userDesc = new JLabel();
	
	String nameCom = new String();
	
	
	JButton botaoPesquisa = new JButton("Pesquisar");
	
	JButton addTema = new JButton("Adicionar tema");
	 
	
	public WelcomePage(Usuario user){
		
		nameCom = user.tituloComu;
		
		welcomeLabel.setBounds(10,0,200,35);
		welcomeLabel.setFont(new Font(null,Font.PLAIN,20));
		welcomeLabel.setText("Hello "+user.nome+"!");
		
		searchLabel.setBounds(300,10,200,35);
		searchLabel.setFont(new Font(null,Font.ITALIC,15));
		
		searchField.setBounds(450,20,150,20);
		searchField.setBorder(BorderFactory.createDashedBorder(Color.BLACK));
		
		prompt.setBounds(300,70,300,300);
		prompt.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		prompt.setLineWrap(true);
        prompt.setWrapStyleWord(true);
        JScrollPane promptScroll = new JScrollPane(prompt);
        promptScroll.setVerticalScrollBarPolicy(
                JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
        promptScroll.setBounds(600,70,15,300);
        promptScroll.setVisible(true);
        
        
        userAge.setBounds(10,80,200,35);
        userAge.setFont(new Font(null,Font.BOLD,12));
        userAge.setText("Idade: " + user.idade);
        
        userDesc.setBounds(10,130,500,35);
        userDesc.setFont(new Font(null,Font.BOLD,12));
        userDesc.setText("Descrição: " + user.desc);
        if(user.desc==null || user.desc.equals("Conte sobre vc!")) userDesc.setText("Descrição não informada");
        
        userInter.setBounds(10,180,500,35);
        userInter.setFont(new Font(null,Font.BOLD,12));
        userInter.setText("Interesses: "+user.interesse);
        if(user.interesse==null) userInter.setText("Interesses não informados");
        
        botaoPesquisa.addActionListener(this);
        botaoPesquisa.setBounds(420,390,100,30);
        
        
        addTema.addActionListener(this);
        addTema.setBounds(50,300,200,30);
        
		frame.add(welcomeLabel);
		frame.add(searchLabel);
		frame.add(searchField);
		frame.add(prompt);
		frame.add(promptScroll);
		frame.add(userAge);
		frame.add(userDesc);
		frame.add(userInter);
		frame.add(botaoPesquisa);
		frame.add(addTema);
		
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(650,470);
		frame.setLayout(null);
		frame.setVisible(true);
		
		
		
		
		
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == botaoPesquisa) {// pesquisamos pelo tema desejado
			String topico = searchField.getText();
			Contents c = new Contents();
			c.getHash(nameCom + ".ser");// formato padronizado dos arquivos do programa
			if(c.getContents().containsKey(topico)) {// caso exista o tema
				Tema te = c.getContents().get(topico);
				prompt.setText(te.text + "\n\nLinks: \n");
				for(int i = 0;i < te.links.length; i++) {
					prompt.append(te.links[i] + "\n");
				}
			}else {
				prompt.setText("Infelizmente o tema que você procurou não existe :(");
			}
		}
		if(e.getSource() == addTema) {
			@SuppressWarnings("unused")
			TemaInput i = new TemaInput(nameCom);// adicionar um novo tema
		}
	}
}
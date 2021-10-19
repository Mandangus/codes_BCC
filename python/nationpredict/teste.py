import pycountry as pc
import numpy as np
import requests
import json

def main():
    print("Enter a name:")
    name = input()
    mensagem_API = requests.get('https://api.nationalize.io/?name=' + name)
    data = mensagem_API.text
    arrumado = json.loads(data)
    print("")
    
    
    for pais in arrumado["country"]:
        nome_pais = pc.countries.get(alpha_2=pais["country_id"])
        prob = (pais["probability"] * 100)
        form_prob = "{:.2f}".format(prob)
        print(pais["country_id"]+ nome_pais.name + " probability " + form_prob + '%')


if __name__ == '__main__':
    main()
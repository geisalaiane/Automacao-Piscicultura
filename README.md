# Bem vindo a página do nosso projeto

Projeto realizado pelos alunos [Fabrício da Silva Selotto](https://gitlab.com/Selotto) e [Geísa Laiane Cardim](https://gitlab.com/geisa), da Fatec Shunji Nishimura, do curso de Big Data no Agronegócio.

## 📋 Introdução

O projeto consiste na criação de um protótipo voltado para a piscicultura, focando na área da alimentação. Trata-se de um alimentador automático para peixes, de baixo custo e uso doméstico, utlizando tecnologia IOT.

## Protótipo
### Estrutural

Para a parte física do alimentador, utilizamos canos pvc de 4 polegadas, um motor 127V de prato de microondas e um motor 127V de ventilador, sendo um para o controle de vazão da ração e o outro para o lanço da mesma. Colocamos o cano PVC em pé onde a ração fica armazenada, e perfuramos a tampa na parte de baixo, onde fixamos o motor com um fio de aço transpassado, que ao girar, deixa cair a ração para o motor de ventilador, onde é lançada para o tanque de água.

[cano](https://w1.ezcdn.com.br/ciadaconstrucao/fotos/zoom/5031fz1/tubo-para-esgoto-barra-de-6m-100mm-amanco.jpg)

### Tecnologia 

Para o controle de ambos os motores, utilizamos um módulo relé 5v, junto a protoboard com uma fonte. Para acionamento utilizamos uma NodeMCU-V3, conectada à rede WIFI, se comunicando via protocólo MQTT, sendo tanto 'publish' quanto 'subscribe', utilizando o broker público 'broker.emqx.io'. Para visualização do histórico de ativação utilizamos o ThingSpeak. 

### Teste



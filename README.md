
## **Estação de Monitoramento Ambiental Local**
**Disciplina:** Internet das Coisas (IoT)  
**Plataforma:** Arduino Uno

### **Descrição**
Projeto de uma estação de monitoramento ambiental local, capaz de medir **temperatura, umidade, luminosidade, chuva e gases poluentes**. O sistema exibe os dados em **LCD 16x2** e aciona alertas visuais (LEDs) e sonoros (buzzer) conforme condições críticas. Também possui **modo standby automático** baseado na detecção de presença (sensor ultrassônico HC-SR04) e controle manual de energia via **botão toggle**, promovendo economia de energia e sustentabilidade.

### **Objetivos**

-   Monitorar parâmetros ambientais em tempo real.    
-   Alertar o usuário sobre condições críticas.    
-   Reduzir consumo de energia durante períodos de inatividade.    
-   Fornecer informações claras via LCD e Serial Monitor.    

### **Componentes e Sensores**

-   **DHT11:** Temperatura e umidade.    
-   **Sensor de luz:** Detecta luminosidade (Claro/Escuro).    
-   **Sensor de chuva:** Mede intensidade da chuva.    
-   **MQ135:** Detecta gases poluentes.    
-   **HC-SR04:** Detecta presença/movimento.    
-   **LCD 16x2 (I2C):** Exibe dados e alertas.    
-   **LEDs (verde, amarelo, vermelho):** Indicadores de status.    
-   **Buzzer:** Alertas sonoros.    
-   **Botão toggle:** Liga/desliga total do sistema.    
-   **Potenciômetro:** Alterna modos de exibição no LCD.    

### **Funcionalidades**

1.  Leitura contínua de todos os sensores.    
2.  Exibição de dados em 3 modos no LCD:    
    -   Temperatura / Umidade        
    -   Luz / Chuva        
    -   Gás / Chuva
        
3.  Alertas por LEDs e buzzer:    
    -   Verde → Normal        
    -   Amarelo → Atenção        
    -   Vermelho + Buzzer → Crítico
        
4.  Modo standby automático com buzzer curto quando não há movimento.    
5.  Controle de energia via botão toggle.    
6.  Log completo das leituras no Serial Monitor.    

### **Código**

-   Inicialização de sensores e LCD.    
-   Função de medição de distância do HC-SR04.    
-   Leitura de sensores analógicos e digitais.    
-   Lógica de alertas e modo standby.    
-   Controle de exibição via potenciômetro.    

### **Aplicação Acadêmica**

-   Desenvolve habilidades em **IoT, sensoriamento, comunicação I2C e lógica de controle**.    
-   Permite análise de **dados ambientais e tomada de decisão baseada em alertas**.    
-   Incentiva **sustentabilidade energética** com modo standby inteligente.

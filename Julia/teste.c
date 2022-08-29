//Apresentacao do Sistema
    /*  Arquivos Necessarios - 
    - arquivo entrada: Aux.txt*/
    char nave[101];
	FILE * entradapre = fopen("Aux.txt", "r");
	while(!feof(entradapre))
	{
	     fgets(nave,100,entradapre);
	     printf("%s",nave);
	}
	fclose(entradapre);
	printf("\n \n");
	FILE * entrada = fopen("PlanetasStarWars.txt", "r");
	
	// Caso o arquivo nao tenha sido aberto
	if (entrada == NULL) 
	{
		printf ("ERRO: O arquivo não pode ser encontrado\n");
		return ERROR;
	}
	/* Caso o Arquivo tenha sido aberto, 
	para cada um de NumPlanetas um planeta 
	eh referenciado                      */
	char Planeta[101];
	
	printf("Lista Planetas da Galaxia\n");
	for(int i = 0; i < NumPlanetas; i++)
	{
	    printf("%d - ", i+1);
        fgets(Planeta,100,entrada);
        printf("%s",Planeta);
	}
	fclose(entrada);
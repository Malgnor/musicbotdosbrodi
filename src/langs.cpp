#include "langs.h"
#include "global.h"

using namespace Global;

void generatePTBRStrings(){

	/* COMMANDS / */

	languages[LANG_PT_BR].COMMAND_ACTIVATE = "ativar";
	languages[LANG_PT_BR].COMMAND_DEACTIVATE = "desativar";
	languages[LANG_PT_BR].COMMAND_CONNECT = "conectar";

	/* INFOS */

	languages[LANG_PT_BR].BOT_ACTIVATED_SUCESS = "O bot agora est\303\241 ativado!";
	languages[LANG_PT_BR].BOT_ACTIVATED_FAIL = "O bot n\303\243o foi ativado!";
	languages[LANG_PT_BR].BOT_DEACTIVATED_SUCESS = "O bot agora est\303\241 desativado!";
	languages[LANG_PT_BR].BOT_DEACTIVATED_FAIL = "O bot n\303\243o foi desativado!";
	languages[LANG_PT_BR].BOT_CONNECT_SUCESS = "Sucesso ao conectar!";
	languages[LANG_PT_BR].BOT_CONNECT_FAIL = "Falha ao conectar!";
	languages[LANG_PT_BR].BOT_ALREADY_CONNECTED = "J\303\241 esta conectado.";

	/* COMMANDS ! */

	languages[LANG_PT_BR].USER_COMMAND_YOUTUBE = "!youtube";
	languages[LANG_PT_BR].USER_COMMAND_HELP = "!ajuda";
	languages[LANG_PT_BR].USER_COMMAND_PLAYING = "!tocando";
	languages[LANG_PT_BR].USER_COMMAND_LENGTH = "!duracao";
	languages[LANG_PT_BR].USER_COMMAND_NEXT = "!proximo";
	languages[LANG_PT_BR].USER_COMMAND_PREV = "!anterior";
	languages[LANG_PT_BR].USER_COMMAND_PAUSE = "!pausar";
	languages[LANG_PT_BR].USER_COMMAND_PLAY = "!tocar";
	languages[LANG_PT_BR].USER_COMMAND_GOTO = "!irpara";

	/* INFOS */

	languages[LANG_PT_BR].BOT_PARAMETER_MISSING = "Faltou par\303\242metro!";
	languages[LANG_PT_BR].BOT_INVALID_PARAMETER = "Par\303\242metro inv\303\241lido!";
	languages[LANG_PT_BR].BOT_ADDED_TO_PLAYLIST = " foi adicionado na playlist.";
	languages[LANG_PT_BR].BOT_HELP_WHEN_ENABLED = "Bem-Vindo ao meu canal de m\303\272sica!\n\
												Comandos dispon\303\255veis: \n\
												!youtube link - Coloca o link na playlist\n\
												!tocando - Mostra a m\303\272sica atual\n\
												!duracao - Mostra duracao da m\303\272sica atual\n\
												!proximo - Pula para a proxima m\303\272sica\n\
												!anterior - Pula para a m\303\272sica anterior\n\
												!pausar - Pausa/despausa m\303\272sica atual\n\
												!tocar - Toca m\303\272sica atual\n\
												!irpara xx - Vai para o momento xx segundos da m\303\272sica\n\
												!irpara x:y - Vai para o momento x minutos e y segundos da m\303\272sica\n\
												!ajuda - Mostra essa mensagem\n";
	languages[LANG_PT_BR].BOT_HELP_WHEN_DISABLED = "Bem-Vindo ao meu canal de m\303\272sica!\n\
												   Atualmente estou desativado.\n\
												   Entre em contato com algum admin para mais info.";
	languages[LANG_PT_BR].BOT_TELNET_NOT_CONNECTED = "Telnet n\303\243o est\303\241 conectado.";
	languages[LANG_PT_BR].BOT_TRY_AGAIN = "Tente novamente!";
	languages[LANG_PT_BR].BOT_MINUTES = "minutos";
	languages[LANG_PT_BR].BOT_SECONDS = "segundos";
	languages[LANG_PT_BR].BOT_AND = "e";
	languages[LANG_PT_BR].BOT_ERROR = "ERRO!";
	languages[LANG_PT_BR].BOT_NECESSARY_VOTES = "votos necess\303\241rios";
	languages[LANG_PT_BR].BOT_NOT_PLAYING = "Digite !play ou a playlist est\303\241 vazia.";

	/* SETTINGS GUI*/

	languages[LANG_PT_BR].GUI_TITLE_SETTINGS = "Configura\303\247\303\265es";
	languages[LANG_PT_BR].GUI_TITLE_COMMANDS = "Comandos";
	languages[LANG_PT_BR].GUI_LABEL_VLC_EXE_PATH = "Caminho do execut\303\241vel do VLC:";
	languages[LANG_PT_BR].GUI_LABEL_MUSIC_CHANNEL = "Canal de m\303\272sica";
	languages[LANG_PT_BR].GUI_BUTTON_USE_CURRENT_CHANNEL = "Usar canal atual";
	languages[LANG_PT_BR].GUI_LABEL_LANGUAGE = "Idioma";
	languages[LANG_PT_BR].GUI_LABEL_RC_PORT = "Porta:";
	languages[LANG_PT_BR].GUI_BUTTON_CONNECT_TO_VLC = "Conectar ao VLC";
	languages[LANG_PT_BR].GUI_BUTTON_CONNECTED = "Conectado";
	languages[LANG_PT_BR].GUI_BUTTON_DEACTIVATE_BOT = "Desativar bot";
	languages[LANG_PT_BR].GUI_BUTTON_ACTIVATE_BOT = "Ativar bot";
	languages[LANG_PT_BR].GUI_BUTTON_ENABLE_DISABLE_COMMANDS = "Habilitar/Desabilitar comandos";
	languages[LANG_PT_BR].GUI_CHB_COMMAND_BY_VOTES = "Comando por votos";
	languages[LANG_PT_BR].GUI_PREFFIX_NECESSARY_VOTES = "Votos necess\303\241rios: ";
}

void generateENUSStrings(){

	/* COMMANDS / */

	languages[LANG_EN_US].COMMAND_ACTIVATE = "activate";
	languages[LANG_EN_US].COMMAND_DEACTIVATE = "deactivate";
	languages[LANG_EN_US].COMMAND_CONNECT = "connect";

	/* INFOS */

	languages[LANG_EN_US].BOT_ACTIVATED_SUCESS = "Bot has been activated!";
	languages[LANG_EN_US].BOT_ACTIVATED_FAIL = "Bot has failed to activated!";
	languages[LANG_EN_US].BOT_DEACTIVATED_SUCESS = "Bot has been deactivated!";
	languages[LANG_EN_US].BOT_DEACTIVATED_FAIL = "Bot has failed to deactivated!";
	languages[LANG_EN_US].BOT_CONNECT_SUCESS = "Connected!";
	languages[LANG_EN_US].BOT_CONNECT_FAIL = "Failed to connect!";
	languages[LANG_EN_US].BOT_ALREADY_CONNECTED = "Already Connected!";

	/* COMMANDS ! */

	languages[LANG_EN_US].USER_COMMAND_YOUTUBE = "!youtube";
	languages[LANG_EN_US].USER_COMMAND_HELP = "!help";
	languages[LANG_EN_US].USER_COMMAND_PLAYING = "!playing";
	languages[LANG_EN_US].USER_COMMAND_LENGTH = "!length";
	languages[LANG_EN_US].USER_COMMAND_NEXT = "!next";
	languages[LANG_EN_US].USER_COMMAND_PREV = "!prev";
	languages[LANG_EN_US].USER_COMMAND_PAUSE = "!pause";
	languages[LANG_EN_US].USER_COMMAND_PLAY = "!play";
	languages[LANG_EN_US].USER_COMMAND_GOTO = "!goto";

	/* INFOS */

	languages[LANG_EN_US].BOT_PARAMETER_MISSING = "Parameter missing!";
	languages[LANG_EN_US].BOT_INVALID_PARAMETER = "Invalid parameter!";
	languages[LANG_EN_US].BOT_ADDED_TO_PLAYLIST = " was added to playlist.";
	languages[LANG_EN_US].BOT_HELP_WHEN_ENABLED = "Welcome to my music channel!\n\
												Commands available: \n\
												!youtube link - Insert the link in the playlist\n\
												!playing - show the title what\'s currently playing\n\
												!length - show the length of what\'s currently playing\n\
												!next - skip to next music\n\
												!prev - skip to previous music\n\
												!pause - pause/unpause what's currently playing\n\
												!play - play the current song\n\
												!goto xx - go to the moment xx seconds of what\'s currently playing\n\
												!goto x:y - go to the moment x minutes and y seconds of what\'s currently playing\n\
												!help - show this message\n";
	languages[LANG_EN_US].BOT_HELP_WHEN_DISABLED = "Welcome to my music channel!\n\
												   Currently i\'m not active.\n";
	languages[LANG_EN_US].BOT_TELNET_NOT_CONNECTED = "Telnet not connected!";
	languages[LANG_EN_US].BOT_TRY_AGAIN = "Try again!";
	languages[LANG_EN_US].BOT_MINUTES = "minutes";
	languages[LANG_EN_US].BOT_SECONDS = "seconds";
	languages[LANG_EN_US].BOT_AND = "and";
	languages[LANG_EN_US].BOT_ERROR = "ERROR!";
	languages[LANG_EN_US].BOT_NECESSARY_VOTES = "necessary votes";
	languages[LANG_EN_US].BOT_NOT_PLAYING = "Type !play or the playlist is empty.";

	/* SETTINGS GUI*/

	languages[LANG_EN_US].GUI_TITLE_SETTINGS = "Settings";
	languages[LANG_EN_US].GUI_TITLE_COMMANDS = "Commands";
	languages[LANG_EN_US].GUI_LABEL_VLC_EXE_PATH = "VLC exe path:";
	languages[LANG_EN_US].GUI_LABEL_MUSIC_CHANNEL = "Music channel";
	languages[LANG_EN_US].GUI_BUTTON_USE_CURRENT_CHANNEL = "Use current channel";
	languages[LANG_EN_US].GUI_LABEL_LANGUAGE = "Language";
	languages[LANG_EN_US].GUI_LABEL_RC_PORT = "Port:";
	languages[LANG_EN_US].GUI_BUTTON_CONNECT_TO_VLC = "Connect to VLC";
	languages[LANG_EN_US].GUI_BUTTON_CONNECTED = "Connected";
	languages[LANG_EN_US].GUI_BUTTON_DEACTIVATE_BOT = "Deactivate bot";
	languages[LANG_EN_US].GUI_BUTTON_ACTIVATE_BOT = "Activate bot";
	languages[LANG_EN_US].GUI_BUTTON_ENABLE_DISABLE_COMMANDS = "Enable/Disable commands";
	languages[LANG_EN_US].GUI_CHB_COMMAND_BY_VOTES = "Commands by votes";
	languages[LANG_EN_US].GUI_PREFFIX_NECESSARY_VOTES = "Necessary votes: ";

}
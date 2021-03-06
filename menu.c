/**************************************************************************************************/
/* Copyright (C) RootAmaris                                                                       */
/*                                                                                                */
/*  FILE NAME             :  menu.c                                                               */
/*  PRINCIPAL AUTHOR      :  RootAmaris                                                           */
/*  SUBSYSTEM NAME        :  menu                                                                 */
/*  MODULE NAME           :  menu                                                                 */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/20                                                           */
/*  DESCRIPTION           :  This is a menu operation program                                     */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by RootAmaris, 2014/09/20
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

#define CMD_MAX_LEN 128

char pInputCmd[CMD_MAX_LEN];

tMenu* CreateMenu()
{
    tMenu *pNewMenu = (tMenu*)malloc(sizeof(tMenu));
    tLinkTable *pNewLinkTable = CreateLinkTable();
    pNewMenu->pMenuHead = pNewLinkTable;
    return pNewMenu;
}

/*create linked list node*/
tCmdNode* CreateCmdNode(char* pNodeCmd, char* pNodeDesc, int (*pNodeOpt)())
{
    tCmdNode *pNewNode;
    pNewNode = (tCmdNode*)malloc(sizeof(tCmdNode));
    if(pNewNode == NULL)
    {
        printf("Error: command node create failed!\n");
        return NULL;
    }
    else
    {
        pNewNode->cmd = pNodeCmd;
        pNewNode->desc = pNodeDesc;
        pNewNode->pOpt = pNodeOpt;
    }
    return pNewNode;
}

int AddCommand(tMenu *pMenu, char* pCommand, char* pDesc, int (*pOpt)())
{
    AddLinkNode(pMenu->pMenuHead, (tLinkNode *)CreateCmdNode(pCommand, pDesc, pOpt));
    return 0;
}

int ShowAllCommand(tMenu *pMenu)
{
    tLinkTable *pLinkTable = pMenu->pMenuHead;
    if(pLinkTable->linkNodeSize == 0)
    {
        printf("There is no command.\n");
        return 2;
    }
    printf("This is my command list:\n");
    tCmdNode *pThisCmdNode;
    pThisCmdNode = (tCmdNode *)GetLinkTableFirst(pLinkTable);
    while(pThisCmdNode != NULL)
    {
        printf("     %s     ", pThisCmdNode->cmd);
        printf("\n");
        pThisCmdNode = (tCmdNode *)GetNextLinkNode(pLinkTable, (tLinkNode *)pThisCmdNode);
    }
    return 0;
}

int ShowAllInformation(tMenu *pMenu)
{
    tLinkTable *pLinkTable = pMenu->pMenuHead;
    if(pLinkTable->linkNodeSize == 0)
    {
        printf("There is no command.\n");
        return 2;
    }
    tCmdNode *pThisCmdNode;
    pThisCmdNode = (tCmdNode *)GetLinkTableFirst(pLinkTable);
    while(pThisCmdNode != NULL)
    {
        printf("\n%s-------%s\n", pThisCmdNode->cmd, pThisCmdNode->desc);
        pThisCmdNode = (tCmdNode *)GetNextLinkNode(pLinkTable, (tLinkNode *)pThisCmdNode);
    }
    return 0;
}


int SearchCondition(tLinkNode *pLinkNode)
{
    tCmdNode *pNode = (tCmdNode *)pLinkNode;
    if(!strcmp(pNode->cmd, pInputCmd))
    {
        return 1;  
    }
    return 0;	       
}

int MenuStart(tMenu *pMenu)
{
    tCmdNode *pThisNode;
    while(1)
    {
        printf("\nftp[Please enter a command]>");
        scanf("%s", pInputCmd);
        if((pThisNode = (tCmdNode *)SearchLinkNode(pMenu->pMenuHead, SearchCondition)) != NULL)
        {
            printf("%s\n", pThisNode->desc);
            if(pThisNode->pOpt != NULL)
            {
                pThisNode->pOpt(pMenu);
            }
        }
        else
        {
            printf("This command is not exist!\n");
	    continue;
        } 
    }
}

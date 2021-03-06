#include "bbslib.h"
#include "identify.h"

int
bbsreg_main()
{
	html_header(1);

#ifdef POP_CHECK
	struct stat temp;
	/*
	if (stat(MY_BBS_HOME "/etc/pop_register/pop_list", &temp) == -1)
	{
		http_fatal("目前没有可以信任的邮件服务器列表, 因此无法验证用户\n");
	}
	
	FILE *fp;
	fp = fopen(MY_BBS_HOME "/etc/pop_register/pop_list", "r");
	if (fp == NULL)
	{
		http_fatal("打开可以信任的邮件服务器列表出错, 因此无法验证用户\n");
	}	
	*/
#endif

	printf("<body>");
	printf("<nobr><center>%s -- 新用户注册<hr>\n", BBSNAME);
	printf
	    ("<font color=green>欢迎加入本站. 以下资料请如实填写. 带*号的项目为必填内容.</font>");
	printf
	    ("<br><font color=green>其中 『 ID 』为您在本站所实际显示的用户名称，不可修改，请慎重填写.</font>");
	printf("<form method=post action=bbsdoreg>\n");
	printf("<table width=100%%>\n");
	printf
	    ("<tr><td align=right>*请输入ID  :<td align=left><input name=userid size=12 maxlength=12> (2-12字符, 必须全为英文字母)\n");
	printf
	    ("<tr><td align=right>*请输入密码:<td align=left><input type=password name=pass1 size=12 maxlength=12> (4-12字符)\n");
	printf
	    ("<tr><td align=right>*请确认密码:<td align=left><input type=password name=pass2 size=12 maxlength=12>\n");
	printf
	    ("<tr><td align=right>*请输入昵称:<td align=left><input name=username size=20 maxlength=32> (2-30字符, 中英文不限)\n");
	printf
	    ("<tr><td align=right>*请输入您的真实姓名:<td align=left><input name=realname size=20> (请用中文, 至少2个汉字)\n");
	printf
	    ("<tr><td align=right>*详细通讯地址/目前住址:<td align=left><input name=address size=40>  (至少6个字符)\n");
#if 0
	printf
	    ("<tr><td align=right>*详细通讯地址:<td align=left><input name=address size=40> (至少6个字符)\n");
	printf("<tr><td align=right>*您的出生年月:\n");
	printf("<td align=left><input name=year size=4 maxlength=4>年");
	printf("<input name=month size=2 maxlength=2>月");
	printf("<input name=day size=2 maxlength=2>日<br>");
	printf
	    ("<tr><td align=right>请输入您的性别: <td align=left><input type=radio name=gender value=0 checked>男 ");
	printf("<input type=radio name=gender value=1>女<br>\n");
	printf("<tr><td align=right>星座显示方式: ");
	printf
	    ("<td align=left><input type=radio name=xz value=0 checked>颜色区分性别 ");
	printf("<input type=radio name=xz value=1>不区分颜色 ");
	printf("<input type=radio name=xz value=2>不显示星座\n");
#endif
	
	printf
	    ("<tr><td align=right>*学校系级或者公司单位:<td align=left><input name=dept size=40>\n");

#ifndef POP_CHECK
	printf
	    ("<tr><td align=right>email地址(可选):<td align=left><input name=email size=40>\n");
#endif	

	printf
	    ("<tr><td align=right>联络电话(可选):<td align=left><input name=phone size=40>\n");
	printf
	    ("<tr><td align=right>校友会或者毕业学校(可选):<td align=left><input name=assoc size=40>\n");
	printf("<tr><td align=right>上站留言(可选):<td align=left>");
	printf("<textarea name=words rows=3 cols=40 wrap=virutal></textarea>");

#ifdef POP_CHECK
	char bufpop[256];
	int numpop = 0;
	char namepop[10][256]; // 注意：最多信任10个pop服务器，要不就溢出了！
	char ippop[10][256];
/*
	while(fgets(bufpop, 256, fp) != NULL)
	{
		if (strcmp(bufpop, "") == 0 || strcmp(bufpop, " ") == 0 || strcmp(bufpop, "\n") == 0)
			break;
		strcpy(namepop[numpop], bufpop);
		fgets(bufpop, 256, fp);
		strcpy(ippop[numpop], bufpop);
		numpop ++;
	}
	fclose(fp);
*/
	printf("<tr><td align=right>*可以信任的邮件服务器列表（新生请选择stu.xjtu.edu.cn）:<td align=left><SELECT NAME=popserver>\n");
	int n = 1;
	while(n <= DOMAIN_COUNT)
	{
//		namepop[n - 1][strlen(namepop[n - 1]) - 1] = 0;
//		ippop[n - 1][strlen(ippop[n - 1]) - 1] = 0;
		
		char tempbuf[512];
		strncpy(tempbuf, MAIL_DOMAINS[n], 256);
		strcat(tempbuf, "+");
		strcat(tempbuf, IP_POP[n]);
		if (n == 1)
			printf("<OPTION VALUE=%s SELECTED>", tempbuf);
		else
			printf("<OPTION VALUE=%s>", tempbuf);

		printf("%s", MAIL_DOMAINS[n]);
		n++;

	}
	printf("</select>\n");
	printf
	    ("<tr><td align=right>*请输入邮箱用户名（新生请输入test）:<td align=left><input name=user size=20 maxlength=20> \n");
	printf
	    ("<tr><td align=right>*请输入邮箱密码（新生请输入test）:<td align=left><input type=password name=pass size=20 maxlength=20> \n");
	printf("<tr>每个信箱最多可以认证 %d 个bbs帐号\n", MAX_USER_PER_RECORD);
	
#endif	

	printf("</table><br><hr>\n");
	printf
	    ("<input type=submit value=提交表格> <input type=reset value=重新填写> <input type=button value=查看帮助 onclick=\"javascript:{open('/reghelp.html','winreghelp','width=600,height=460,resizeable=yes,scrollbars=yes');return false;}\"\n");
	printf("</form></center>");
	http_quit();
	return 0;
}

// finger.c
/*
(1) allow wizard (arch+) to be invisible to players.
(2) disable group finger for players --- no more dummy guess. we encourage role playing.
------	Modified by Silencer@fy4, 12/02/03
*/

inherit F_CLEAN_UP;

void create()
{
	seteuid(getuid());
}

int main(object me, string arg)
{
	if (me->query_temp("timer/big_cmd")+2 > time())
		return notify_fail("������ȽϺķ�ϵͳ��Դ��ÿ��ֻ��ִ��һ�Ρ�\n");
	else if (!wizardp(me))
		me->set_temp("timer/big_cmd",time());

	if( !arg ) {
		if( !wizardp(me) )
			return notify_fail("fingerָ���������������\n");		
/*		if( (int)me->query("sen") < 100 )
			return notify_fail("��ľ����޷����С�\n");
		if( !wizardp(me) )
		{
			me->receive_damage("sen", 100);
			me->start_more("", FINGER_D->finger_all(0), 0);
		}
		else*/
			me->start_more("", FINGER_D->finger_all(1), 0);

	} else {
		if( (int)me->query("sen") < 50 )
			return notify_fail("��ľ����޷����С�\n");
		if( !wizardp(me) )
			me->receive_damage("sen", 50);
		write( FINGER_D->finger_user(arg,(wizardp(me) || arg == (string)me->query("id"))) );
	}
	return 1;
}


int help(object me)
{
  write(@HELP

[0;1;37m����������������������������������������������������������������[0m
[0;1;36mָ���ʽ : 	finger [ʹ��������][0m
[0;1;37m����������������������������������������������������������������[0m   

���ָ����ʹ��������,����ʾ�й�ĳ����ҵ�����, Ȩ�޵����ϡ�
�����Ҫ��������һЩ����Ƿ����ߣ�����ʹ��friendָ�
 
see also : who

[0;1;37m����������������������������������������������������������������[0m 
HELP
    );
    return 1;
}
 
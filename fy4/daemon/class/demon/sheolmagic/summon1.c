#include <ansi.h>
inherit SSERVER;

int conjure(object me, object target)
{
	object soldier;
	int	spells,lvl;
	int duration, time;
	
    if(me->query("class")!="demon")
		return notify_fail("ֻ��ħ�̵ĵ��Ӳ��ܹ�ʹ��ҹ��ͨ�鷨��\n");
		    
    spells = me->query_skill("spells");
    if(me->query_skill("sheolmagic",1) < 35 )
        return notify_fail("��Թ���ٻ�����Ҫ35����ҹ��ͨ�鷨��\n");

	time = 3600;
	if (!userp(me)) time = 60;
	duration = me->query("timer/demon_guardian1")+ time -time();
	if (duration>0)	
		return notify_fail("���ٻ�ħ������ȴ�"+ duration/60 +"���ӡ�\n");

    
	if( !me->is_fighting() )
		return notify_fail("ֻ��ս���в����ٻ����ݣ�\n");

	message_vision(HIB"$N"HIB"�૵����˼������˫��һ�ӣ�һ�������Եص�����\n\n"NOR, me);
	message_vision("		"BMAG YEL"��Թ���ٻ���\n\n"NOR,me);
	
	me->set("timer/demon_guardian1",time());
	seteuid(getuid());
	soldier = new("/obj/npc/guardian1");
	soldier->move(environment(me));
	soldier->invocation(me, spells);
	soldier->set("possessed", me);
	me->perform_busy(2);
	return 1;
}



/*

���������������X�Y
���������������U�t�r
���������������U���t�r
���������������U�����t�r
���������������U��������
���������������^�k�k�k�_

��������������- FengYun - ������
������������annie 08.2003
������dancing_faery@hotmail.com
*/
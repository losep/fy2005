// annie 07.2003
// dancing_faery@hotmail.com



#include <ansi.h>
#include <combat.h>
inherit SMART_NPC;
void smart_fight();

void create()
{
	object weapon;
        set_name("«��", ({ "lu di","lu","di" }) );

		set("class","moon");
		set("title",BLU"�������"NOR);
		set("nickname",CYN"�á�������������"NOR);

		set("always_duxin",1);

    	set("attitude","friendly");


set("str",1);
set("force_factor",300);

        set("gender", "Ů��" );

		set("age",27);

	set("chat_chance",1);
	set("chat_msg", ({
		"«�ӿ����Ͱ͵������㣬����������������������ö�����\n",
		"«������ָͷ������һ�̡������̡������̡����˼��Ѿ���������û�������ˡ���\n",
		"«��ҧ���´����۹�ʱ��ʱ��Ʈ������̯���ϣ�һ����Թ����ɫ��\n",
	}) );



        set("combat_exp", 6600000);

    	set("chat_chance_combat", 100);
    	set("chat_msg_combat", ({
	     (: smart_fight() :),
        }) );


        
        set_skill("blade", 200);
        set_skill("sword", 200);
        set_skill("lefthand-sword", 200);
        set_skill("dodge", 200);
        set_skill("parry", 200);
        set_skill("chillblade", 200);
        set_skill("13-sword", 150);
        set_skill("unarmed", 200);
        set_skill("hammer", 200);
        set_skill("longfenghuan", 186);
        set_skill("lingxi-zhi", 190);
		set_skill("force",200);
		set_skill("jingxing",200);
		set_skill("spicyclaw",400);
		set_skill("venusfinger",200);
		set_skill("xifengying",180);

		set_skill("divineforce",200);
		set_skill("daimonsword",200);
		set_skill("demosword",200);
		set_skill("xiaodao",200);
		set_skill("zen",200);
		
		set_skill("strategy",300);
		set_skill("leadership",300);

	set_skill("magic", 240);
	set_skill("essencemagic", 240);
	set_skill("blade", 240);
	set_skill("heavendance", 240);
	set_skill("beilongblade", 280);
	set_skill("axe", 300);
	set_skill("xuanyuan-axe", 200);

		set_skill("six-sense",300);
		set_skill("fall-steps",220);
		set_skill("meng-steps",220);

		set_skill("throwing",240);
		set_skill("tanzhi-shentong",240);

		set_skill("chillblade", 230);
		set_skill("stormdance", 200);

		map_skill("throwing", "tanzhi-shentong");

		map_skill("magic", "essencemagic");
        map_skill("axe", "xuanyuan-axe");
        map_skill("force", "divineforce");
        map_skill("hammer", "longfenghuan");
        map_skill("blade", "chillblade");
        map_skill("unarmed", "spicyclaw");
        map_skill("sword", "demosword");
        map_skill("parry", "chillblade");
        map_skill("dodge", "stormdance");

		set("death_msg",CYN"\n$N����죬��Թ����Ҳ�ã����˾Ͳ�����ˡ���\n"NOR);

		setup();
		weapon=carry_object("/d/xiangsi/npc/obj/iceblade");
		weapon->wield();
		
        weapon=carry_object("/obj/armor/cloth");
        weapon->set_name("����˿��", ({ "cloth" }) );
		weapon->set("value",0);
		weapon->wear();

}


int kill_ob(object who)
{
    command("loveme "+who->query("id"));
	if (!is_fighting())
		ccommand("perform dodge.shuangtianxuewu");
	::kill_ob(who);
	return 1;
}


void smart_fight()
{
//	ccommand("perform mantianhuayu");
		ccommand("perform dodge.shuangtianxuewu");
	return;
}



int accept_object(object me, object obj)
{
	if (obj->query("food_supply"))
	{
		ccommand("emote �����۾������ס�������Ŀ��Գ�ô��");
		ccommand("emote ü����Ц�ؽӹ�"+obj->name()+"��ƴ����������лл��лл��");
		message_vision("«�ӽ����е�" + obj->name() + "�Եøɸɾ�����\n", me);
		ccommand("emote ̧��ͷ��ˮ��ˮ��Ĵ����޹��������㣬�·����ʣ�����ô��");
		perform_busy(1);	
		return 1;
	}
	command("emote ҡҡͷ����������������ö�����");
	return 0;
}

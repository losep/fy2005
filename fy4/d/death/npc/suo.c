// Copyright (C) 1995, by Tie Yu and Daniel Yu. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.

// 2009 FengYun
// Edit by hippo 2009.11
// Т�� ����

inherit NPC;
#include <ansi.h>
int story();
int give_me_it(object me);
int give_me_it_zouzhe(object me);

int annie_drug()
{
	object me = this_player();

	if (REWARD_D->riddle_check(me,"�������")==9){
		give_me_it(me);
		return 1;
	}
			
	if (REWARD_D->riddle_check(me,"�������") == 5)
	{
		message_vision(query("name")+"΢΢һЦ����ͷ����÷��������֪������ˡ�\n",me);
		message_vision(query("name")+"������ֻ��Ϊ��Ѱ��"HIR"������"NOR"��"HIB"������"NOR"���ұ㽫���̲ݸ��㡣\n",me);
		REWARD_D->riddle_set(me,"�������",6);
		return 1;
	}
	message_vision(query("name")+"΢ҡ���ף���Ϊ���ҵ����������������������ã����ܸ��㡣\n",me);
	return 1;
}


void create()
{
        set_name("���", ({ "xiaonu", "nu" }) );
        set("gender", "Ů��" );
        set("long","
��Т�����������µ���ӡ������ʫ�ޣ����������ֱ���Ω�������̡�
̫��������͵ݳ����ǡ��Ժ������ӣ����������䡣СŮʹ���ԣ�
���߲����������������£�˼�Ÿ衶�����������Ĵ����ѣ������Ｄ����
ʥ��Т�ĵۣ���Ȼ�����顣���к��㴣�����һ��ӡ���\n");
        set("age", 24);
		set("per", 30);
		set("attitude","friendly");
        
        set("inquiry", ([
			//"Т��" : "���巢����֮��ĸ������֮�����������죬��Т֮�ˣ��������ݡ�\n",
			//"xiao" : "���巢����֮��ĸ������֮�����������죬��Т֮�ˣ��������ݡ�\n",
			"Т" : CYN"����Ը���ٸ���Ϊū澣��游��������ҵ���Ը�ǵõ�"YEL"ТŮ��"CYN"���׸��ҵĸ��ף�\n",
			"xiao" : CYN"����Ը���ٸ���Ϊū澣��游��������ҵ���Ը�ǵõ�"YEL"ТŮ��"CYN"���׸��ҵĸ��ף�\n",
			"Т��" : CYN"����Ը���ٸ���Ϊū澣��游��������ҵ���Ը�ǵõ�"YEL"ТŮ��"CYN"���׸��ҵĸ��ף�\n",
			"ī" : HIC"�����ŵ��ܸ��аɣ�\n",
			"ТŮ��" : CYN"ТŮ����"YEL"���ֻ�"CYN"�Լ�"YEL"��ʯ"CYN"ͬʱ����Ҫ�������Ϸ���������һ���ǳɡ�\n",
			"���ֻ�" : CYN"������ֻ����и��ĺ��壺\n
				"HIC"��һ�������˳���������³ɡ�ף�����߹�\n"CYN"
				"HIG"�ڶ����������졢�Ҹ������ࡢ���桢��ƽ��ϣ�������ˡ������ĵ׵İ���\n"CYN"
				"HIW"���������: ����İ���Լ����\n"CYN"
				"HIY"���Ķ����: �ǻ���\n"CYN"
				"HIB"��������: �򰮶���Щ������\n"CYN"
				"HIC"���һ��������ˣ� �˼��ƣ���������������ʥ�\n"CYN"
				",
			"��ʯ" : CYN"����һ���ܹ�ʹ���������������ٵ�л������ʯͷ����˵��а��̨����Ʒ�����ڿ������䵽����̷������ˡ�\n",
			          	"���̲�" : 	(: annie_drug :),
          	"���б���":	"action��������˺죬΢Ц���\n",
			"������": "�ҵ����������̲ݵ�ʱ������ͬһ���ط���������\n�ǲ��ʺ���Ѫ��Ҷ��˷֣���һ���Ϳ����ϳ����ˡ�\n",
			"������": "�⻨��ϲ���ռ���֮�أ��Ӷ��ϵ��������������¶����������������ڡ�\n",
			"����": 			 (: story :),
			"ͬһ���ط�":  	(: story :),
			"�ط�":  		(: story :),
			"̶":	 "action���΢΢Ц��Ц˵�����Ǹ����վ��ĵط�����������ȥ�ء�\n",
			"̶��":  "action���΢΢Ц��Ц˵�����Ǹ����վ��ĵط�����������ȥ�ء�\n",
      ]) );
        set("combat_exp", 2200000);
        set_skill("xiaodao", 200);
        set("skill_public",1);
        set("chat_chance", 1);
    		set("chat_msg", ({
						"������ֹ��������巢����֮��ĸ������֮�����������죬��"YEL"Т"NOR"֮�ˣ��������ݡ� \n",
			    	}) );   
		set_temp("apply/attack",200);
		set_temp("apply/dodge", 200);
		set_temp("apply/parry", 200);
        setup();
        carry_object("/obj/armor/ghost_cloth")->wear();
}


int is_ghost() { return 1; }

int story(){
		tell_object(this_player(),CYN"���˵�������ݡ������������̲ݣ�ԭ����������ɽ��ͬһ��ط������ģ�����ϡ��
��ҩ�ģ��Ҹ���Ǩ���ͣ��ұ�������������̲����ֵ��˶��ߵ�ɽ�ϣ�ԭ����Ҫ��ȥ
ȡ�������ݵģ�û�뵽�Ҹ�Ϊ���ݺ�������Զ��������Ҳ����Ҳû�л�ȥ����

������ĵ�̾�˿�����Ҳ��֪�������Ƿ�����̶�ߣ��������ǿɰ���С�ڹ꣬��
���ǻ����������������\n"NOR);
		return 1;
}


int give_me_it(object me)
{
	object x;
	x=new(__DIR__"obj/grass");
	if (!x->move(me))
		x->move(environment(me));
	message_vision("���΢Ц������л��\n��ӵݸ�$Nһ��С�ݡ�\n",me);
	return 1;
}

int give_me_it_zouzhe(object me)
{
	object x;
	x=new(__DIR__"obj/zouzhe");
	if (!x->move(me))
		x->move(environment(me));
	message_vision("��ӵݸ�$Nһ��"HIW"����"NOR"��\n��Ӽ�����"CYN"������������\n"NOR,me);
	return 1;
}

int accept_object(object who, object ob)
{
	object me = who;
///////////////////////////////////////////Т������//////////////////////////////////////////////////////	
	if (ob->query("name") == HIG"ТŮ��"NOR)
	{
		if (ob->query("lore"))
		{
			//message_vision("$N�ӹ�"+ ob->name() + "�����ϲ����̫���ˣ�̫���ˣ��Ḹ�о��ӡ���\n",me);
			message_vision("���һ��Īչ����"CYN"������Ͻ���֮�£�����ù�����������\n"NOR,me);
			if (REWARD_D->riddle_check(me,"Т�в���") == 1)
			{
				REWARD_D->riddle_set(me,"Т�в���",2);
				return 0;
			}
		}
		//message_vision("$N���е�˵���㾡Ȼ���������СŮ�ӿ���Ц��\n", me);			
		//message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 0;
	}

	if (ob->query("name") == "��ֽ" && REWARD_D->riddle_check(me,"Т�в���") == 3)
	{
		if (ob->query("lore"))
		{
			message_vision("��ӽӹ�"+ ob->name() + "˵�������鷳�ٰ�СŮ��ȡ��"YEL"��"NOR"��"HIC"ī"NOR"��"YEL"��"NOR"����\n",me);
			REWARD_D->riddle_set(me,"Т�в���",4);
			return 1;
		}
		//message_vision("$N���е�˵���㾡Ȼ���������СŮ�ӿ���Ц��\n", me);			
		//message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 0;
	}

	if (REWARD_D->riddle_check(me,"Т�в���") == 4)
	{
		if (ob->query("name") == "��" || ob->query("name") == "ī" || ob->query("name") == "��̨")
		{
			string *material_names=({ "��","ī","��̨" });
			string ob_name;
			int success, makeup_ok,i;
			object book;
			
			
			if (!REWARD_D->riddle_check(me,"Т�в���")) {
					command("say ��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n");
				return 1;
			}
			
			ob_name= ob->query("name");
			success=1;
			makeup_ok=0;
			for(i=0;i<3;i++)
			{
				if(ob_name==material_names[i])
				{
					if(me->query_temp("marks/death/xiaonv/"+ob_name))
					{
						command("say �ⶫ���㲻�Ǹ������ˡ���\n");
						return 1;
					}
					me->set_temp("marks/death/xiaonv/"+ob_name,1);
					command("say ���Ǵ����л�ˡ�");
					makeup_ok=1;
				}
				success=success*me->query_temp("marks/death/xiaonv/"+material_names[i]);
			}
			if(!success) return makeup_ok; 
				
			me->delete_temp("marks/death/xiaonv/");	
			
			tell_object(me,"���˵��"CYN"�������ˣ����Եȣ���\n"NOR);
			give_me_it_zouzhe(me);
			REWARD_D->riddle_set(me,"Т�в���",5);
	    return 1;
	  }
	}
	
	if (ob->query("name") == HIR"������"NOR && REWARD_D->riddle_check(me,"Т�в���") == 6)
	{
		if (ob->query("lore"))
		{
			message_vision("��ӽӹ�"+ ob->name() + "�����ϲ��"CYN"��̫���ˣ�̫���ˣ��Ḹ�о��ӡ���\n"NOR,me);
			message_vision("�������$n�������������"CYN"��СŮ������Ϊ����Ը��Т���������ڡ���\n"NOR, ob, me);
			me->set("free_learn/xiaodao", 1);
			REWARD_D->riddle_done(me, "Т�в���", 20, 1);
			return 1;
		}
		//message_vision("$N���е�˵���㾡Ȼ���������СŮ�ӿ���Ц��\n", me);			
		//message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 0;
	}

///////////////////////////////////////////����Т������//////////////////////////////////////////////////////	

	if (REWARD_D->riddle_check(me,"�������") != 6 && REWARD_D->riddle_check(me,"�������") != 7 && REWARD_D->riddle_check(me,"�������") != 8 )
	{
		message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 1;
	}

	if (REWARD_D->riddle_check(me,"�������") == 6)
	{
		if (ob->query("name") == HIB"������"NOR && ob->query("real_flower") == 1)
		{
			REWARD_D->riddle_set(me,"�������",7);
			message_vision("���΢Ц�������Ǵ����л�ˡ�\n",me);
			return 1;
		}
		else if (ob->query("name") == HIR"������"NOR && ob->query("real_flower") == 2)
		{
			REWARD_D->riddle_set(me,"�������",8);
			message_vision("���΢Ц�������Ǵ����л�ˡ�\n",me);
			return 1;
		}
		message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 1;
	}
	
	if (REWARD_D->riddle_check(me,"�������") == 7)
	{
		if (ob->query("name") == HIR"������"NOR && ob->query("real_flower") == 2)
		{
			REWARD_D->riddle_set(me,"�������",9);
			give_me_it(me);
			return 1;
		}
		message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 1;
	}

	if (REWARD_D->riddle_check(me,"�������") == 8)
	{
		if (ob->query("name") == HIB"������"NOR && ob->query("real_flower") == 1)
		{
			REWARD_D->riddle_set(me,"�������",9);
			give_me_it(me);
			return 1;
		}
		message_vision("��Ӷ�$N΢Ц�������յظ��öȶ�ȱ����л������\n",me);
		return 1;
	}
	message_vision("��Ӷ�$N΢Ц���������ˣ��㻹��ȥ������ʦô��\n",me);
	return 1;
}

int recognize_apprentice(object ob)
{
     if(ob->query("free_learn/xiaodao"))
     		return 1;
		 return 0;
}

int prevent_learn(object me, string skill)
{
  	if (skill != "xiaodao")
  	{
      		command("shake");
      		command("say �ҿ�ֻ��Ӧ����Т������");
      		return 1;
  	}
  	return 0;
}

int prevent_shown(object me, string skill)
{
	if (me->query("free_learn/xiaodao")	&& skill == "xiaodao")
		return 0;
	
	return 1;
}
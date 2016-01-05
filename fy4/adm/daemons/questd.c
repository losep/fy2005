// questd.c
// Copyright (C) 1995 - 2001, by FengYun Workshop. All rights reserved.
// This software can not be used, copied, or modified in any form without
// the written permission from authors.
// 

#pragma optimize all
inherit F_ANNIE;
#include <ansi.h>

string wait_period(int timep);
int basic_quest_reward(int exp); 
int special_reward(object me, string qname);
void give_reward(object who,object accomplisher, mapping quest);
void log_quest(object me, object owner, mapping quest, int reward_exp, int used_time, int base);
int holiday_bonus = 200;   	// 05/20/2008 fixed to x2 reward  ע��������������� 
int chance = 20;
int level_chance = 80;

void create() {
    seteuid(ROOT_UID);
}


int query_holiday(){
	return holiday_bonus;	 
}

int set_holiday(int bonus){
	holiday_bonus = bonus;
	return bonus;
}

//	�˺������Quest��Ʒ
//  The difference between "Ѱ" and "ɱ" is
//  "ɱ" checks and gives credit to each teammate, "Ѱ" searches for one then ends loop.
int accept_quest_object(object who, mixed ob, object me)
{
    int val, delay, i, gr;
    string name; 
    object* mem;
    mapping quest;

	if (objectp(ob))
    if(ob->is_character()) {
		return 0;
    }

	if (objectp(ob)) name = ob->query("name");
	else if (stringp(ob))	name = ob;
	else	return 0;
		
    mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
    for(i=0; i<sizeof(mem); i++) {
	if (mem[i]) {
	    if(mapp(quest = mem[i]->query("quest")) 
	      && name == quest["quest"]
	      && (string)(quest["quest_type"]) == "Ѱ"
	      && (time() - mem[i]->query("quest_time") <= 900)) {

		give_reward(mem[i], who, quest);
		return 1;
	    }
	}
    }

    return 0;
}

//	����Quest��

int give_quest(object who, mapping me)
{
    mapping quest,qmirror,qex;
    int i, num, combatexp, max_exp, num_file, n1, n2, time;
    string tag = "_default";
    string qstr;
    object* mem;

    //	�Է���һ    
    if(who->is_ghost() || who->is_zombie()) {
	tell_object(who,"���겻��Ҫ����������������ʦ������������BUG������\n");	
	return notify_fail("\n");
    }

    //	���е�Quest��û�����	
    time = who->query("quest/duration")>1 ? who->query("quest/duration") : 900; 
    if(qex =  who->query("quest") && (time() - who->query("quest_time") < time)) {
		return 0;
    }

    //	Cancel�����һ��ʱ�仹û����	
    if((who->query("next_time")) > time()) {
	return 0;
    }

    max_exp = 0;
    combatexp =0;

    //	�ҳ�һ��team�ﾭ����ߵ���Ա
    mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
    i = sizeof (mem);
    while (i--)	{
	if (mem[i]) {
	    max_exp = mem[i]->query("combat_exp");
	    if (max_exp > 15000000) max_exp = 15000000;
	    combatexp = (max_exp>combatexp) ? max_exp : combatexp;
	}
    }


    //	ѡ���ĸ�quest�ļ���ע��ǰ�����п���ѡ��
    num_file = combatexp / 1000;

    // ���5����������cancel���Σ�50%������һ������qlist_repeat
    if (who->query("marks/quest_cancel")>=2)
		n1 = 2;
    else if (who->query("marks/quest_cancel")>=1)
		n1 = 10;
    else
		n1 = 15;

    if(!random(n1))	{ 	
		tag = "_repeat";
		if (sizeof(mem)>1) 
	    	quest = QUEST_D(tag)->query_quest(combatexp/1000);
		else {
			quest = QUEST_D(tag+"_solo")->query_quest(combatexp/1000);
    	}
    }

    // DEBUG LINE   
   if (wizardp(who)) {
    	if (who->query("wiz_quest")=="repeat") 
    	{
    		tag = "_repeat";
    	   	quest = QUEST_D(tag)->query_quest(combatexp/1000);
    	} else if (who->query("wiz_quest")=="special") {
    		tag = "_special";
    	   	quest = QUEST_D(tag)->query_quest(combatexp/1000);
    	}  		
	}
	// DEBUG LINE END
	
    if (!sizeof(quest) || !quest) {
	if (!random(30)) {
	    tag = "_special";
	    if (sizeof(mem)>1)
	    	quest = QUEST_D(tag)->query_quest(combatexp/1000);
		else
			quest = QUEST_D(tag+"_solo")->query_quest(combatexp/1000);
	} 
    } else
    {
	// ��� qlist_repeat Ϊ�棬delete repeat cancel mark.
		who->delete_temp("timer/quest_cancel");
		who->delete("marks/quest_cancel");
    }	

    //	CHANNEL_D->do_sys_channel("sys", sprintf("%O\n",quest) );	

    if (!sizeof(quest) || !quest) {
		if( num_file < 100) 		tag="_small";		
		else if( num_file <= 1000) 	tag="_middle";
		else if (num_file <= 5000) 	tag="_large";
		else	tag="_super"; 
		
		quest = QUEST_D(tag)->query_quest(combatexp/1000);	
    }

    if (tag == "_special" || tag == "_repeat") {
		qmirror = mapping_copy(quest);// nip pointer bug.
		who->set("quest",qmirror);
		who->set("quest_time", (int)time());
		who->add_temp("quest_number", 1);	
		qstr = quest["short"];						
//		CHANNEL_D->do_sys_channel("sys",sprintf("%O ?? %O: %s", quest, qmirror, qstr));
    } else 
    {
		who->set("quest", quest);
		who->set("quest_time", (int)time());
		who->add_temp("quest_number", 1);
		if (quest["quest_location"])
	    	qstr = HIW"��"+quest["quest_location"];
		else qstr="";

		if(quest["quest_type"] == "Ѱ") {
	    	qstr += HIW"�һء�"NOR + quest["quest"] + HIW"����" 
	    	+ me["employer"] + HIW"��"NOR;
		} else if(quest["quest_type"] == "ɱ") {
	    	qstr += HIW"��" + me["employer"] + HIW"ɱ�ˡ�"NOR
	    	+ quest["quest"] + HIW"����"NOR;
		}
    }

//	I don't like Ѱ at higher level (>=90), ǿ����ת��
	if (F_LEVEL->get_level(combatexp)>= level_chance && quest["quest_type"] == "Ѱ" 
			&& (random(100)<chance || who->query("chuili_unfinished"))) { 
		tag = "_repeat";
		quest = ([
			"quest":	"̽�ô�����ɮ",
			"long":		"�������˵�����������������֯Ƶ������㲻��ȥ�ҳ������ĺ��д���������",
			"short":	"ȥ�������Ҵ�����ɮ����������֯������",
			"owner":	"monk",		
			"location":	"������",		
			"duration":		1800,			
			"cancel": -1,	// CC +200% 
			"difficulty":	400,			
			"exp_l":		6000,						
			"exp_h":		10000,					
			"quest_type":	"special",		
		]),
		qmirror = mapping_copy(quest);// nip pointer bug.
		who->set("quest",qmirror);
		who->set("quest_time", (int)time());
		who->add_temp("quest_number", 1);
		who->set("chuili_unfinished",1);	// ���Markֻ���������Ż���ʧ������㲻�������С�Ѱ�������ɴ���	
		qstr = quest["short"];						
	}

    //	����Quest�����ݣ�
    i = sizeof(mem);
    while (i--) {
	if (objectp(mem[i])) {
	    if (mem[i] == who) {
		if (tag == "_special" || tag=="_repeat")
		    tell_object(who, CYN + quest["long"] + "\n"NOR);
		else
		    tell_object(who, WHT + me["name"] + WHT"˵������" + qstr + NOR"\n");
	    }
	    else 
		tell_object(mem[i], WHT + "���� "+ who->name() + WHT" ���ڵ�������: " + qstr + NOR"\n");

	}
    }

    /*	CHANNEL_D->do_sys_channel("qst", sprintf("%s��%s(%s)%s\n",
		    me["name"],
		    HIW + who->name(),
		    HIW + who->query("id"),
		    HIW + qstr));*/

    return 1;
}


/*  Quest ������ʽ��ֻ�������йأ����������影���ĸ���
		base = �ܽ����߶�Ӧ�ȼ��Ļ����ѣ��������� *75% (+ full_team ����100%)
		bonus1 = Quest �Ѷȣ�x1--x2
			(1)	�Ƚ���ɱ+5, 
			(2)	�Ƚ�Զ+5, (������Ʒ) After 5M, this is no longer the case.
			(3)	�϶�������Σ��+10-15, 
		bonus2 = Team	+5% per person to 25% top

	4.0 system base�ο�:
		0-10k, 		20 - 23
		10-800k, 	32 - 116
		880k-2.2M: 	116 - 233
		2.2M+		131+ random(91) --- 260

*/


void give_reward(object who, object accomplisher, mapping quest) 
{
	int team_size, i, level, base, d_bonus, team_bonus, combat_exp, silver, money, q_bonus, half;
	int h_bonus;
	string reward_msg;
	object ob;
	object* mem;

	mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
	team_size = sizeof(mem);


	// special quest��exp_bonus�����ãѣ��������Ǹ��˾���ֵ����
	if( quest["exp_bonus"] != 0 ) {
		q_bonus = quest["exp_bonus"];
	} else {
		q_bonus = who->query("combat_exp")/1000;
	}

	// reward money
	if( q_bonus > 3000 ) {
		money = 20+random(30);
	}else if( q_bonus > 1000 ) {
		money = 15+random(25);
	}else if( q_bonus > 100 ) {
		money = 10+random(20);
	}else {
		money = 5+random(10);
	}

	if( team_size ) {
		for( i = 0; i < team_size; i++ ) {
			// ע�⣬�����õ���F_LEVEL, ֱ�� query("level")�õ����������ﵽ�����lvl
			level = F_LEVEL->get_level(mem[i]->query("combat_exp"));
			base = REWARD_D->quest_reward(level);

// DEBUG LINE
#ifdef NONENCRYPTED_WRITE
	if( who->query("wiz_qreward") ) {
		base = base*who->query("wiz_qreward");
	}
#endif
// DEBUG LINE END
			if( quest["difficulty"] ) {
				d_bonus = quest["difficulty"];
			}
			team_bonus = (team_size-1)*5;
			// ���ս�������ֵ�� REWARD CAPPED at 10M, ����Ľ���ability����ֻ��������pot
			combat_exp = base*(100+d_bonus+team_bonus)/100/team_size;

			// Holiday rewards, 50=*0.5, 100 = *2, 200= *3 
			combat_exp = combat_exp*(100+query_holiday())/100;

			half = 1;
			if( mem[i]->query("death/half_quest") < 0 ) { // ������������ʧ
				// lv 50�����£���������24Сʱ���϶�����revive, Ҳû��Penalty
				if( level < 50 && mem[i]->query("death/time") + 86400 < time() ) {
					mem[i]->delete("death/half_quest");
					mem[i]->delete("death/exp_lost");
					mem[i]->set("death/revived", 1);
					tell_object(mem[i],"��ϲ�����������ʧ�ڣ���Сʱ���Զ���ʧ�ˣ�\n");
				} else {
					half = 2;
					mem[i]->add("death/half_quest",combat_exp/half);
				}
			}
			combat_exp = combat_exp/half;

			if( mem[i]->query("env/ability" ) 
				&& F_LEVEL->get_level(mem[i]->query("combat_exp"))>=80
				&& mem[i]->query("saved_quest")/60/100 < mem[i]->query("learned_ability")+6 ) {
				mem[i]->add("saved_quest", 60/team_size/half);
				if( query_holiday() )
					mem[i]->add("saved_quest", 60/team_size/half*query_holiday()/100);
			} else {
				if( mem[i]->query("combat_exp") >= 10000000 ) {
					mem[i]->add("extra_exp", combat_exp);
				}
				if( mem[i]->query("combat_exp") < 10000000 ) {
					mem[i]->add("combat_exp", combat_exp);
				}
				if( mem[i]->query("combat_exp") >= 10000000 ) {
					mem[i]->set("combat_exp",10000000);
				}
			}
			silver = money*(100+d_bonus+team_bonus)/100/team_size;
			silver = silver/half;

			// Holiday rewards, 50=*0.5, 100=*2, 200=*3
			silver = silver*(100+query_holiday())/100;
			// low level 25% extra silver bonus
			if( level < 50 ) {
				silver = silver*150/100;
			}

			// ֱ�����ʣ�
			mem[i]->add("deposit", silver*100);

			if( mem[i] != accomplisher) {
				if( mem[i] == who ) {
					reward_msg =YEL"�������"+accomplisher->name()+"��ɣ���ľ���ֵ�����" + "������" + chinese_number(silver) + "�����ӡ�\n\n" + NOR;
				} else {
					reward_msg =YEL+ who->name()+"������"+accomplisher->name()+"��ɣ���ľ���ֵ�����" + "������" + chinese_number(silver) + "�����ӡ�\n\n" + NOR;
				}
			} else {
				reward_msg = (accomplisher==who) ? WHT : WHT+"���� "+who->name()+" ��";
				reward_msg +="��������ɣ���ľ���ֵ����ˣ�����" +chinese_number(silver) + "�����ӡ�\n" + NOR;
				if (random(100)>85)  //add by ldb ���Ӷ��⽱����Ϊ��ƽ������о����ٵ�ID��������Զ׷��������
				{
                 ob=new("/obj/wiz_toy/baoxiang1");
                 ob->move(this_player());
          		 tell_object(mem[i],HIY"��������ڿ�Ŭ�����ؽ���������һ����\n");
				}
			}
			tell_object(mem[i],reward_msg);
			if( half == 2 ) {
				if( mem[i]->query("death/half_quest") < 0 ) {
	//				tell_object(mem[i],"�����������������������������Ϊ��������\n");
	//				tell_object(mem[i],"�����������ٶȣ���Լ����Ҫ" + (-mem[i]->query("death/half_quest")/combat_exp)+ "��������û�гͷ��ˣ�\n");
				} else {
					mem[i]->delete("death");
					tell_object(mem[i],HIW"����ϲ�����������ʧ�Ѿ�ȫ�������ˣ���\n");
				}
			}
		}
	}

	who->set("quest", 0); // Quest����
	if( who->query("cont_quest") < 20 ) {
		who->add("cont_quest",1);
	}
	accomplisher->add("FINISH_QUEST", 1);
	return;
}

string wait_period(int timep) {
    int t, d, h, m, s;
    string delay = "";

    t = timep;
    s = t % 60;             t /= 60;
    m = t % 60;             t /= 60;
    h = t % 24;             t /= 24;
    d = t;

    if(d) {
	delay += chinese_number(d) + "��";
    }
    if(h) {
	delay += chinese_number(h) + "Сʱ";
    }
    if(m) {
	delay += chinese_number(m) + "��";
    }
    if(s) {
	delay += chinese_number(s) + "��";
    }
    return delay;
}

//	�ͻ��Ľ���
int flower_delivery_reward(object me, object who,object flower) {
    mapping delivery;
    int exp,pot,success_time,amount;
    object coin;

    if (!mapp(delivery = flower->query("delivery"))) return 0;
    if (base_name(who) != delivery["receiver"]) return 0;
    if (flower->query("delivery_time") != me->query("delivery_time")) return 0;

    success_time = (int)me->query("marks/delivery_success");
    me ->set("marks/delivery_success",success_time+1);

    if (me->query("quest/quest")== "�ͻ�") 
	amount = 10;
    else
	amount = 1;

    coin = new("/obj/money/silver");
    coin->set_amount(random(amount) + amount);

    switch (random(3))
    {
	    case 0:
		message_vision("$N�˷ܵؾ���һ������������������ô�� ��\n",who);
		break;
	    case 1:
		message_vision("$N����ض�$nһЦ˵����л��л��\n",who,me);
		break;
	    case 2:
		message_vision("$N���洺�磬Ц��ӯӯ��������$n���������Ǹ���ģ��������ˡ���\n",who,me );	
		break;
    }

/*  if (coin)
    {
		coin->move(me);
		tell_object(me,who->name()+"�ݸ���"+chinese_number(amount)+"�����ӡ�\n");
    }*/

    if (me->query("quest/quest")== "�ͻ�") {
			special_reward(me,"�ͻ�");
    }    
    me->delete("delivery");
    me->delete("delivery_time");

    /*
    if(!undefinedp(quest["fin_func"])) {
	    call_other(this_object(),quest["fin_func"],me,who,quest_item);
    }*/
    if(flower) {
		destruct(flower);
    }
    return 1;
}

//	��¼һЩ���ߵĽ���ֵ
void log_quest(object me, object owner, mapping quest, int reward_exp, int used_time, int base) 
{
    if (reward_exp <1000) return;

    log_file("QUEST_REWARD",
      sprintf("%s(%s) ����� %s(%s) ������ ��  %s %s �Ѷ� %d ʱ�� %s\n�������飺%d used_time: %d  base: %d\n",
	me->name(1), geteuid(me), owner->name(1), geteuid(owner), quest["quest_type"], quest["quest"], quest["difficulty"], ctime(time()), 
	reward_exp, used_time, base));

}

//	Verify if you or team member has the qname quest	
int verify_quest(object me, string qname){

    mapping quest;
    object *mem;
    int i;

    mem = pointerp(me->query_team()) ? me->query_team() : ({ me });
    for(i=0; i<sizeof(mem); i++) {
	if (objectp(mem[i])) {
	    if(mapp(quest = mem[i]->query("quest")) 
	      && mem[i]->query("quest/quest") == qname)
		return 1;
	}
    } 
    return 0;
}	

//	should be included in the one above.. but well, too late	
mapping return_quest(object me, string qname){

    mapping quest;
    object *mem;
    int i;

    mem = pointerp(me->query_team()) ? me->query_team() : ({ me });
    for(i=0; i<sizeof(mem); i++) {
	if (objectp(mem[i])) {
	    if(mapp(quest = mem[i]->query("quest")) 
	      && mem[i]->query("quest/quest") == qname)
		return quest;
	}
    } 
    return 0;
}	

/*	�˺�����Special Quest����
	There are two kinds of Special Quest in FY2005
	Rewards will always be shared among teammates.
	(1) Those only can be finished by Quest_owner
		Example: �󲿷ֵ���һ�ε�,��ʫ���ܵ�
		�÷����ڣѣ���������ʱcall special_reward(me, quest_name)��
			��speical_reward��ԺϷ��Խ��м�鲢give_reward(me, me, quest)������

	(2) Those can be finished by any of team members
		If two or more teammates have same quests, only one can be finished at a time.
		It should be the achiever first, then pick one from the group
		Example: ɱ����һ����ף�
		�÷����ڣѣ���������ʱ��For best flexibility,
			�Լ�����accomplisher && who's_quest"_is_done.
			����ֱ��CALL give_reward(quest_owner, accomplisher, quest)

*/



int special_reward(object me, string qname) {

    mapping quest;
    int i;

    if ( mapp(quest = me->query("quest")) && me->query("quest/quest") == qname)
    {
	if (time()-me->query("quest_time") < quest["duration"])
	{
	    give_reward(me, me, quest);
	    return 1;
	}
	tell_object(me,"�ܿ�ϧ����û���ڹ涨��ʱ�����������\n");
	me ->set("quest",0);
	me ->delete("annie_quest");		// just a precaution.
	me ->delete_temp("annie_quest");
    }

    return 1;
}

int give_quest_list(object who, mapping me)
{
    mapping qmirror,qex;
    int i, num, combatexp, max_exp, num_file, n1, n2, time;
    string tag = "_default";
    string qstr;
    object* mem;
	mapping quest;
	
    int j, k, count, s;
    mapping *quest_list = ({});
    
    quest_list = allocate(3);

    //	�Է���һ    
    if(who->is_ghost() || who->is_zombie()) {
		tell_object(who,"���겻��Ҫ����������������ʦ������������BUG������\n");	
		return notify_fail("\n");
    }

    //	���е�Quest��û�����	
    time = who->query("quest/duration")>1 ? who->query("quest/duration") : 900; 
    if(qex =  who->query("quest") && (time() - who->query("quest_time") < time)) {
		return 0;
    }

    //	Cancel�����һ��ʱ�仹û����	
    if((who->query("next_time")) > time()) {
		return 0;
    }

    max_exp = 0;
    combatexp =0;

    //	�ҳ�һ��team�ﾭ����ߵ���Ա
    mem = pointerp(who->query_team()) ? who->query_team() : ({ who });
    i = sizeof (mem);
    while (i--)	{
	if (mem[i]) {
	    max_exp = mem[i]->query("combat_exp");
	    if (max_exp > 15000000) max_exp = 15000000;
	    combatexp = (max_exp>combatexp) ? max_exp : combatexp;
	}
    }


    //	ѡ���ĸ�quest�ļ���ע��ǰ�����п���ѡ��
    num_file = combatexp / 1000;

    
    j = 0;
    k = 0;
       
    while (j <3 && k< 10) {
      	// ���ֻ��һ�� non-normal quest
	    quest = ([]);
	    
	    if (!s) {
		    if(!random(15))	{ 	
				tag = "_repeat";
				if (sizeof(mem)>1) 
			    	quest = QUEST_D(tag)->query_quest(combatexp/1000);
				else {
					quest = QUEST_D(tag+"_solo")->query_quest(combatexp/1000);
		    	}
		    	s = 1;
		    }
	
		    if (!sizeof(quest) || !quest) {
				if (!random(30)) {
				    tag = "_special";
				    if (sizeof(mem)>1)
				    	quest = QUEST_D(tag)->query_quest(combatexp/1000);
					else
						quest = QUEST_D(tag+"_solo")->query_quest(combatexp/1000);
				} 
				s = 1;
			}
		}
		
    //	CHANNEL_D->do_sys_channel("sys", sprintf("%O\n",quest) );	

	    if (!sizeof(quest) || !quest) {
			
			if( num_file < 100) 		tag="_small";		
			else if( num_file <= 1000) 	tag="_middle";
			else if (num_file <= 5000) 	tag="_large";
			else	tag="_super"; 
			
			quest = QUEST_D(tag)->query_quest(combatexp/1000);	
	    }

	    if (tag == "_special" || tag == "_repeat") {
			qmirror = mapping_copy(quest);// nip pointer bug.
			qmirror["quest_des"] = quest["short"];
	//		CHANNEL_D->do_sys_channel("sys",sprintf("%O ?? %O: %s", quest, qmirror, qstr));
	    } else 
	    {
			if (quest["quest_location"])
		    	qstr = HIW"��"+quest["quest_location"];
			else qstr="";
			if(quest["quest_type"] == "Ѱ") {
		    	qstr += HIW"�һء�"NOR + quest["quest"] + HIW"����" 
		    	+ me["employer"] + HIW"��"NOR;
			} else if(quest["quest_type"] == "ɱ") {
		    	qstr += HIW"��" + me["employer"] + HIW"ɱ�ˡ�"NOR
		    	+ quest["quest"] + HIW"����"NOR;
			}
			qmirror = mapping_copy(quest);
			qmirror["quest_des"] = qstr;
	    }
	    
	    quest_list[j] = mapping_copy(qmirror);
	    j++;
	    k++;
	}
	
    CHANNEL_D->do_sys_channel("sys", sprintf("%s quest_list is %O",HIW + who->name(), quest_list));

    return 1;
}


int dungeon_reward(object quester, string name, object*	rewardee, int d_bonus)
{
	int team_size, i, level, base, n, combat_exp, silver, money, q_bonus, half;
	string reward_msg;
	object ob;
	object* mem;

	if( name == "������ɮ������") {
		mem = rewardee;
		team_size = sizeof(mem);
	
		// reward money, ���ˡ�400 bonus ���� /4 --> gold
		money = d_bonus/4;
		if( team_size ) {
			for( i = 0; i < team_size; i++ ) {
				// ע�⣬�����õ���F_LEVEL, ֱ�� query("level")�õ����������ﵽ�����lvl
				level = F_LEVEL->get_level(mem[i]->query("combat_exp"));
				base = REWARD_D->quest_reward(level);

				// ���ս�������ֵ�� REWARD CAPPED at 10M, ����Ľ���ability����ֻ��������pot
				combat_exp = base*(d_bonus)/100/team_size; // ���ﲻ��Ҫ�ӣ������ˣ�d_bonus�������影��

				// Holiday rewards, 50=*0.5, 100=*2, 200=*3 
				combat_exp = combat_exp*(100+query_holiday())/100;
				half = 1;
				if( mem[i]->query("death/half_quest") < 0 ) {
					// ������������ʧ
					if( level < 50 && mem[i]->query("death/time")+86400 < time() ) {
						// lv 50�����£���������24Сʱ���϶�����revive, Ҳû��Penalty
						mem[i]->delete("death/half_quest");
						mem[i]->delete("death/exp_lost");
						mem[i]->set("death/revived",1);
						tell_object(mem[i],"��ϲ�����������ʧ�ڣ���Сʱ���Զ���ʧ�ˣ�\n");
					} else {
						half = 2;
						mem[i]->add("death/half_quest", combat_exp/half);
					}
				}
				combat_exp = combat_exp/half;

				if( mem[i]->query("env/ability") 
					&& F_LEVEL->get_level(mem[i]->query("combat_exp")) >= 80
					&& mem[i]->query("saved_quest")/60/100 < mem[i]->query("learned_ability")+6 ) {
					mem[i]->add("saved_quest", 60*d_bonus/100/team_size/half);
					if( query_holiday() ) {
						mem[i]->add("saved_quest", 60*d_bonus/100/team_size/half*query_holiday()/100);
					}
				} else {
					if( mem[i]->query("combat_exp") >= 10000000 ) {
						mem[i]->add("extra_exp", combat_exp);
					}
					if( mem[i]->query("combat_exp") < 10000000 ) {
						mem[i]->add("combat_exp", combat_exp);
					}
					if( mem[i]->query("combat_exp") >= 10000000 ) {
						mem[i]->set("combat_exp",10000000);
					}
				}

				silver = money / team_size;
				silver = silver/half;
				// ֱ�����ʣ�
				mem[i]->add("deposit",silver*100);

				if( mem[i] != quester ) {
					reward_msg =YEL+"�����Э���������"+ quester->name()+"�Ĵ�����ɮ������ľ���ֵ�����" + combat_exp + "������" + chinese_number(silver) + "�����ӡ�\n\n" + NOR;
				} else {
					reward_msg =YEL+ "������˴�����ɮ��������ľ���ֵ�����" + combat_exp + "������" + chinese_number(silver) + "�����ӡ�\n\n" + NOR;
				}
				tell_object(mem[i], reward_msg);

				if( half == 2 ) {
					if (mem[i]->query("death/half_quest") < 0 ) {
	//					tell_object(mem[i],"�����������������������������Ϊ��������\n");
	//					tell_object(mem[i],"�����������ٶȣ���Լ����Ҫ" + (-mem[i]->query("death/half_quest")/combat_exp)+ "��������û�гͷ��ˣ�\n"); 	
					} else {
						mem[i]->delete("death");
						tell_object(mem[i],"����ϲ�����������ʧ�Ѿ�ȫ�������ˣ���\n");
					}
				}
			}
		}

		quester->delete("private_maze");
		quester ->set("quest", 0);
		quester->delete("quest_time");
		quester->set("chuili_unfinished", 0); // ���Ƿ�����˴���ɮ����
		if( quester->query("cont_quest") < 20 ) {
			quester->add("cont_quest",1);
		}

		quester->add("FINISH_QUEST",1);

	}
	return 1;
}

int set_chance(int num){
	chance = num;
	return 1;
}


int set_level(int num){
	level_chance = num;
	return 1;
}

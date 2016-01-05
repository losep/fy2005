#include <ansi.h>
#include <weapon.h>
inherit MUSKET;
void create()
{
        set_name(HIY"����ǹ"NOR, ({ "matchlock musket" }) );
        set_weight(10000);
        set_max_encumbrance(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long",
"����ǹ�Ľṹ�ǣ�ǹ����һ�����乳���乳��һ�˹̶���ǹ�ϣ���
��������ת����һ�˼г�һȼ�յĻ�����ʿ������ʱ�����ֽ�����
�乳����������ѹ��ʹ������ȼ�ڻ�ҩ��������ǹ����װ�ĵ��跢
���ȥ���ƣɣңţ���"
);
                set("value", 0);
                set("no_stack",1);
//                set("no_drop",1);
                set("material", "steel");
                set("level_required",0);
                set("wield_msg", "$N��$n������磬���ֳ�ǹ��\n");
                set("unequip_msg", "$N�����е�$n�һر���\n");
        }
        ::init_musket(50);

}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
	int dam;
	dam = (int) me->query("max_force")/40;
	dam = COMBAT_D->magic_modifier(me, victim, "gin", dam);
	victim->receive_damage("gin",dam,me);
    return HIR"��Ȫ��ǹ�ƾ����������·���������Ѫâʹ$n�����ɢ����ƣ������\n"NOR;
}
*/

void init()
{
       add_action("do_get1", "get");
       add_action("do_put1", "put");
       add_action("do_prime", "prime");
       add_action("do_clear", "clear");
//     add_action("do_use", "fishing");
       add_action("do_fire", "fire");
}

int do_get1(string arg)
{
	string get_from;
  if( !arg ) return notify_fail("��Ҫ����ʲ�ᶫ����\n");
  if (sscanf(arg, "%s from %s", arg, get_from)==2)
  {
  	if (get_from==this_object()->query("id"))
  	{
  		message_vision("��ʹ��ר��ָ�����ǹ�š����ạ̃ţ��ң�\n"NOR,this_player());
			return 1;
		}
	}
	return 0;
}

int do_put1(string arg)
{
  string put_in;
  if( !arg ) return notify_fail("��Ҫ��ʲ�ᶫ���Ž����\n");
  if (sscanf(arg, "%s in %s", arg, put_in)==2)
  {
  	if (put_in==this_object()->query("id"))
  	{
			message_vision("��ʹ��ר��ָ����װ��ҩ�����Уңɣͣţ�\n"NOR,this_player());
			return 1;
		}
	}
	return 0;
}

int do_prime(string arg)
{
	int i,powder=0,bullet=0;
	object *inv;
	object powderi,bulleti,into_powderi,into_bulleti;
	inv = all_inventory(this_player());
	
	if( !arg ) return notify_fail("��װ��ҩ��ʽ�Уңɣͣ� �ǣգΣУϣףģţ�\n");
	if (arg=="gunpowder") 
	{
		  message_vision("$N�������ӿ�ʼ��װ��ҩ������\n"NOR,this_player());
			tell_object(this_player(),"check1...ok\n"NOR);
			for(i=0; i<sizeof(inv); i++)
		  {
		  	if(inv[i]->query("id") == "gun powder") {powder = 1; powderi = inv[i];}
		   	if(inv[i]->query("id") == "iron bullet") {bullet = 1; bulleti = inv[i];}
			}
			tell_object(this_player(),"check2...ok\n"NOR);
			if (!sizeof(all_inventory(this_object())))
			{
				if(powder && bullet)
				{
					tell_object(this_player(),"check3...ok\n"NOR);
					if (powderi->query_amount() >= 3)
					{
						call_out("do_prime_2", 6, powderi, bulleti, into_powderi, into_bulleti,environment(this_player()));	
						this_player()->start_busy(4);
					} else {
					tell_object(this_player(),"check5...ok\n"NOR);
					tell_object(this_player(),"��ҩ�������޷�������װ��\n"NOR);
					}
				} else {
					tell_object(this_player(),"check6...ok\n"NOR);
					tell_object(this_player(),"û�е�ҩ�ˣ���ʲô��װ��\n"NOR);
				}
			} else {
					tell_object(this_player(),"ǹ�����Ѿ��ж����ˣ��޷��ٴ���װ��\n"NOR);
			}
	} else {
			tell_object(this_player(),"��װ��ҩ��ʽ�Уңɣͣ� �ǣգΣУϣףģţ�\n"NOR);
	}
	return 1;
}

void do_prime_2(object powderi,object bulleti,object into_powderi,object into_bulleti)
{
	tell_object(this_player(),"check4...ok\n"NOR);
	powderi->add_amount(-3);
	bulleti->add_amount(-1);
	into_powderi = new("/d/chengdu/obj/gun_powder.c");
	into_powderi->set_amount(3);
  into_powderi->move(this_object());
	into_bulleti = new("/d/chengdu/obj/iron_bullet.c");
	into_bulleti->set_amount(1);
  into_bulleti->move(this_object());
	message_vision("��װ��ϣ�$NѸ�ٵ�վ��������\n"NOR,this_player());
	this_player()->stop_busy();
	return;
}

int do_clear(string arg)
{
	int i,powder_dust;
	object *inv,powder_dusti;
	inv = all_inventory(this_object());

	if( !arg ) return notify_fail("���ǹ�Ÿ�ʽ�ạ̃ţ��� �ģգӣ�\n");
	if (arg=="dust") 
	{
		  if (this_player()->query_temp("timer/ct_musket_heart") + 12 > time())
		  	return notify_fail(this_object()->name()+"ǹ�Ź��̣��ָ���û�취������\n");
		  	
		  message_vision("$N����һ����ϸ���ǹ�š�����\n"NOR,this_player());
			tell_object(this_player(),"check1...ok\n"NOR);
			for(i=0; i<sizeof(inv); i++)
		  {
		  	if(inv[i]->query("id") == "powder dust") {powder_dust = 1; powder_dusti = inv[i];}
			}
			tell_object(this_player(),"check2...ok\n"NOR);
			if(sizeof(inv)) 
			{
				tell_object(this_player(),"check3...ok\n"NOR);
				if(powder_dust) {
						call_out("do_clear_2", 6, powder_dusti, environment(this_player()));	
				  	this_player()->start_busy(4);
				} else {
				tell_object(this_player(),"check5...ok\n"NOR);
				tell_object(this_player(),"����װ�õĵ�ҩ�����������ǿ�ϧ�ˣ�\n"NOR);
				}
			} else {
			tell_object(this_player(),"check6...ok\n"NOR);
			tell_object(this_player(),"ǹ���ﶼ�ɾ��ķ����ˣ�û��Ҫ�������˰ɣ�\n"NOR);
			}
	} else {
			tell_object(this_player(),"���ǹ�Ÿ�ʽ�ạ̃ţ��� �ģգӣ�\n"NOR);
	}
	return 1;
}

void do_clear_2(object powder_dusti)
{
	tell_object(this_player(),"check4...ok\n"NOR);
	destruct(powder_dusti);
	message_vision("ǹ�������ɣ�$NѸ�ٵ�վ��������\n"NOR,this_player());
	this_player()->stop_busy();
	return;
}

/*
int do_use(string arg)
{
        object *inv,bait;
        inv = all_inventory(this_object());
        //tell_object(this_player(),"���ͳ�һ��" + this_object()->name() + "��\n");
        bait=inv[0];
        tell_object(this_player(),"���ͳ�һ��" + bait->name() + "��\n");
        //environment(this_player())->fish_notify(this_object(),0);
        return 1;
}
*/

/*
int fish_notify(object obj){
   	object me, room, fish, *inv, bait;
   	int i,llvl;

   	me = this_player();
   	llvl = (int)me->query("kar");

	inv = all_inventory(obj);
	if(sizeof(inv) == 0){
		message("vision",me->name() + "�ͳ���" + obj->name() + "�ַ��˻�ȥ��\n", environment(me), me);
     	tell_object(me, obj->name() + "��û�ж���ô���Ե����� ? \n");		
		return 1;
	}		
	for(i=0; i<sizeof(inv); i++) {
		if(inv[i]->query("fish_bait")) {
			bait = inv[i];
      		message_vision("$N���������Ͼ����Ŀ�ʼ������ \n" , me);
      		me->start_busy(3);
      		if(llvl > 15 && random(20) < llvl) {
            		tell_object(me, "��������ע�⵽��ͷѩ�׵�ʯͷ���ƺ���һ��ڰߡ�\n");
            		me->set_temp("marks/bridge", 1);
      		} else if(random(300) < llvl) {
            	tell_object(me, "��������ע�⵽��ͷѩ�׵�ʯͷ���ƺ���һ��ڰߡ�\n");
            	me->set_temp("marks/bridge", 1);
      		}
      		remove_call_out("do_fishing");              
      		call_out("do_fishing", 5, me, bait);			
			return 1;
		} 
	}
   	tell_object(me, "���õĶ���̫�԰� ? \n");			
	return 1;
}

void do_fishing(object me, object bait)
{
   object 	fish;

   if(me && environment(me) == this_object()) {
   message_vision("$N�ܿ��ֳ�����һ�����, " , me);
   switch (random(3)) {
      case 0:
         message_vision("ȴʲô��û������ ! \n", me);
         break;
      case 1:
         message_vision("ʲô��û������ , ���ȴ������� !!  \n", me);
         destruct(bait);
         break;
      case 2:
         message_vision("�㹳�ϵ���һ���� !!  \n", me);
         fish = new(__DIR__"obj/fish");
         fish->move(me);
         destruct(bait);
         break;
      }
   }
   return;
}
*/

int do_fire(string arg)
{
	object ob, me, *inv,powderi,bulleti;
	int i,shoot_error=0;
  inv = all_inventory(this_object());
		
	if(!this_object()->query("equipped")) return notify_fail(this_object()->name()+"û��װ����ǹ���������\n");
	
	if(!this_player()->query_skill("musket",1)) return notify_fail(this_object()->name()+"����������û�ǹʹ�ã��Ͳ�Ҫ����������Ц�ˣ�\n");
	
	if (sizeof(inv) == 0) 
			return notify_fail(this_object()->name()+"û�е�ҩ�޷������\n");

	if (!arg) return notify_fail("��Ҫ��˭��\n");
	me=this_player();
    	
  if (me->query_temp("timer/ct_musket_heart") + 0 > time())
 		return notify_fail(this_object()->name()+"�ո�ʹ�ù�����ǹ���ڻظ��С�\n");
    		
  if( environment(me)->query("no_fight")
 	 || environment(me)->query("no_magic") 
 	 || environment(me)->query("no_spells"))
 	 return notify_fail("���ⲻ��͵Ϯ��\n");
    	
  ob=present(arg,environment(me));
  if (!objectp(ob) || !living(ob)) 
  	return notify_fail(this_object()->name()+"ֻ�ܶԻ������ʹ�á�\n");
    	
  if (userp(me) && me!= ob)
	if (!COMBAT_D->legitimate_kill(me, ob)) {
		if (stringp(ob->query("NO_KILL")))
			return notify_fail(ob->query("NO_KILL"));
		if (stringp(ob->query("NO_PK")))
			return notify_fail(ob->query("NO_PK"));	
	else 
		return notify_fail("���޷��������ˡ�\n");
	}
		
	if (me->is_busy())
		return notify_fail("��������æ��\n");
	
		/*if (!me->is_fighting(ob))
				return notify_fail( this_object()->name()+ "�����������ģ��ɲ���ȥ�������ˡ�\n");*/
			
  if (ob == me)
  	return notify_fail("СС��;��Լ�������\n");
    	
	for(i=0; i<sizeof(inv); i++)
  {
  	if(inv[i]->query("id") == "powder dust") {shoot_error = 1;}
  	if(inv[i]->query("id") == "gun powder") {powderi = inv[i];}
		if(inv[i]->query("id") == "iron bullet") {bulleti = inv[i];}
	}
			
	if (shoot_error)
  	return notify_fail(this_object()->name()+"��ǹ���в��������޷������������ʹ�ãạ̃ţ����ų���\n");

	message_vision(HIR"\n$N"HIR"����"+this_object()->name()+HIR"��׼Ŀ�겢��ȼ�˻�����\n"NOR,me,ob);
	call_out("do_fire2", 6, me, ob, inv,powderi, bulleti, environment(this_player()));	
	this_player()->start_busy(4);
	return 1;
}

void do_fire2(object me,object ob,object *inv,object powderi,object bulleti)
{
	object target,powder_dusti;
	int i,damage,damage2=0,damage3=0,damage4=0;
	string msg;	
	
	damage2 = (int)this_object()->query("weapon_prop/damage");
	damage3 = (int)powderi->query("base_weight");
	damage4 = (int)bulleti->query("base_weight");

    	
  damage = 500 + (me->query_skill("musket") + damage2 * 5 + damage3 * 10 + damage4 * 2) * F_LEVEL->get_level(me->query("combat_exp")) /5; 
  //damage = 500 +  * (extra + cloud/2) /5;	
  if (damage < 1800) damage = 1800;	// ��֤������1800   	
    	
  //message_vision(HIR"\n$N"HIR"����"+this_object()->name()+HIR"��׼Ŀ�겢��ȼ�˻�����\n"NOR,me,ob);
  me->set_temp("timer/ct_musket_heart",time());
    	
  target = ob;
    	
  if (COMBAT_D->do_busy_attack(me, target, "nine-moon-claw/weiwoduzun","unarmed", 700, 10))
  {
   	msg = RED"����һ���������$n�ĲҺ���Ҳ�ѱ��ǹ���ֻ��ǰ˲��Ѫ���ɣ�$n�����˿�һ��ʹ��ı������������$N��\n" NOR;
   	damage = COMBAT_D->magic_modifier(me, target, "kee", damage);
   	target->receive_wound("kee", damage, me);
   	message_vision(msg, me, target);
   	COMBAT_D->report_status(target,0);
  }
  else {
  	msg = CYN"$n��ͷһ�����������һ�����죬�ڻ�ɫ���̶�ʱ�������죡\n";
		message_vision(msg, me, target);
	}
    		
  ob->kill_ob(me); 
	//add("ammo",-1-random(2));
	   	
	for(i=0; i<sizeof(inv); i++)
	{
		//bait = inv[0];
	  destruct(inv[i]);	   	
	}
	powder_dusti = new("/d/chengdu/obj/powder_dust.c");
	powder_dusti->set_amount(1);
	powder_dusti->move(this_object());
  //me->perform_busy(3);
  me->stop_busy();
  return;
}

int is_container() { return 1; }
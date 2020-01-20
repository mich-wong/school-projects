#ifndef _HISTORY_TRANSACTION_HPP_
#define _HISTORY_TRANSACTION_HPP_

#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

#include "project3.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//



Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,
                         unsigned int month_date,  unsigned year_date,
                         bool buy_sell_trans,  unsigned int number_shares,
                         double trans_amount )
{
    symbol = ticker_symbol;
    day = day_date;
    month = month_date;
    year = year_date;
    if (buy_sell_trans)
    {
        trans_type = "Buy";
    }
    else if (!buy_sell_trans)
    {
        trans_type = "Sell";
    }
    
    shares = number_shares;
    amount = trans_amount;
    p_next = nullptr;
    
    this->trans_id = assigned_trans_id;
    assigned_trans_id++;
    
    
    set_acb(0.0);
    set_acb_per_share(0.0);
    set_share_balance(0.0);
    set_cgl(0.0);
    
    
}


// Destructor
// TASK
//

Transaction::~Transaction()
{
    
}

//p_new_trans -> get_symbol();
//(*p_new_trans).getsymbol();
// these are the same thing


// TASK
// Overloaded < operator.
//

bool Transaction::operator<(Transaction const &other )
{
    
    if (this->get_year() < other.get_year())
    {
        return true;
    }
    else if ( this->get_year() > other.get_year())
    {
        return false;
    }
    else // if the years are the same
    {
        if (this->get_month() < other.get_month())
        {
            return true;
        }
        else if (this->get_month() > other.get_month())
        {
            return false;
        }
        else// if the months are the same
        {
            if (this->get_day() < other.get_day())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";
    
    
    if ( get_trans_type() ) {
        std::cout << "  Buy  ";
    } else { std::cout << "  Sell "; }
    
    std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK
//

History::History()
{
    p_head = nullptr;
}


// Destructor
// TASK
//

History::~History()
{
    Transaction *p_traverse = get_p_head();
    while(p_traverse!=NULL)
    {
        Transaction *delete_next = p_traverse->get_next();
        delete p_traverse;
        p_traverse = delete_next;
    }
    
    
}


// TASK
// read_transaction(...): Read the transaction history from file.
//

void History::read_history()
{
    ece150::open_file();
    ece150::next_trans_entry();
    
    //populate the head
    p_head = new Transaction(ece150::get_trans_symbol(),ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
    
    Transaction *transaction;
    
    while(ece150::next_trans_entry())
    {
        
        transaction = new Transaction(ece150::get_trans_symbol(),ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
        
        insert(transaction);
        
    }
    
    ece150::close_file();
}


// insert(...): Insert transaction into linked list.
//

void History::insert(Transaction *p_new_trans)
{
    if (get_p_head() == NULL)
    {
        p_head = p_new_trans;
    }
    else
    {
        Transaction *p_traverse{get_p_head()};
    
        while(p_traverse->get_next() != NULL)
        {
            p_traverse = p_traverse->get_next();
        
        }
        p_traverse->set_next(p_new_trans);
    }
    
}

// TASK
// sort_by_date(): Sort the linked list by trade date.
//

void History::sort_by_date()
{
    
    Transaction *p_node = p_head;
    Transaction *p_sorted_head = NULL;
    Transaction *p_lead;
    bool new_list = true;
    
    //insertion sort

    while (p_head!=NULL)
    {
        p_node = p_head;
        p_head = p_head->get_next();
        
        //start of a new list
        if(new_list)
        {
            p_sorted_head = p_node;
            p_sorted_head ->set_next(NULL);
            new_list = false;
        }
        else
        {
            p_lead = p_sorted_head;
            
            //if the value of the node is less than the value of the head, assign a new head
            if ((*p_node) < (*p_lead))
            {
                p_node->set_next(p_sorted_head);
                p_sorted_head = p_node;
                
            }
            else
            {
                //if the values are in order and the list has not finished, keep searching
                while(p_lead->get_next()!=NULL && (*p_lead->get_next())<(*p_node))
                {
                    p_lead = p_lead->get_next();
                }
                
                //once the value is found, or we are at the end of the list, insert the node
                
                p_node->set_next(p_lead->get_next());
                p_lead->set_next(p_node);
                
            }
            
        }

    }
    
    //change the new head of the list to the head of the sorted list
    p_head = p_sorted_head;
    
}


// TASK
// update_acb_cgl(): Updates the ACB and CGL values.
//

void History::update_acb_cgl()
{
    Transaction *p_traverse = p_head;
    double acb{0};
    double acb_per_share{0.0};
    unsigned int share_balance{0};
    double cgl{0};
    
    while(p_traverse != NULL)
    {
        // if it's a buy
        if(p_traverse ->get_trans_type())
        {
            
            acb = acb + p_traverse->get_amount();
            p_traverse->set_acb(acb);
            
            share_balance = share_balance + p_traverse->get_shares();
            p_traverse->set_share_balance(share_balance);
            
            acb_per_share = acb/share_balance;
            p_traverse ->set_acb_per_share(acb_per_share);
            
            p_traverse->set_cgl(0.0);
            
            
        }
        else
        {
            p_traverse ->set_acb_per_share(acb_per_share);
            acb = acb - (p_traverse->get_shares() * p_traverse->get_acb_per_share());
            p_traverse ->set_acb(acb);
            
            share_balance = share_balance - p_traverse->get_shares();
            p_traverse ->set_share_balance(share_balance);
            
            
            cgl = p_traverse->get_amount() - (p_traverse->get_shares() * p_traverse->get_acb_per_share());
            p_traverse ->set_cgl(cgl);
            
        }
        
        p_traverse = p_traverse->get_next();
        
    }
    
}



// TASK
// compute_cgl(): )Compute the ACB, and CGL.
//

double History::compute_cgl(unsigned int year)
{
    Transaction *p_traverse = p_head;
    double cgl{0.0};
    
    while(p_traverse != NULL)
    {
        if (year == p_traverse->get_year())
        {
            cgl = cgl + p_traverse->get_cgl();
        }
        p_traverse = p_traverse ->get_next();
    }
    
    return cgl;
    
    
}




// TASK
// print() Print the transaction history.
//

void History::print()
{
    std::cout << "===== BEGIN TRANSACTION HISTORY =====" << std::endl;
    
    Transaction *p_traverse{p_head};
    
    
    while(p_traverse!=NULL)
    {
        p_traverse->print();
        p_traverse= p_traverse->get_next();
        
    }
    
    std::cout << "===== END TRANSACTION HISTORY =====" << std::endl;
    
}




// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif

